import pandas as pd
import numpy as np
from pandas import *
import plotly 
import plotly.graph_objs as go
from IPython.display import HTML
import dash
import dash_core_components as dcc
import dash_html_components as html
import dash_colorscales
import dash_bootstrap_components as dbc
from dash.dependencies import Input, Output, State

## Dataframe processing
# A) Load absolute values
# this output was generated using the verfploeter tool
prepend_df = pd.read_csv("./dataset/prepend+withdraw-dataframe.csv", sep=";")
#prepend_df.drop('HND',1,inplace=True)
prepend_df.drop('HND',axis=1,inplace=True)
#prepend_df.drop('unknown',1,inplace=True)
prepend_df.drop('unknown',axis=1,inplace=True)
prepend_df.head(1)

# B) get percentage
# ignore first column 
data = prepend_df.iloc[:,1:8]
df_prepend_percent = data.div(data.sum(axis=1), axis=0).mul(100).round(3) 
# put back the column
df_prepend_percent.insert(0, column='bgp', value=prepend_df['bgp'] )
df_prepend_percent.head(3)

# C) diff from baseline
# data = df_prepend_percent

# get baseline values
data_baseline  = df_prepend_percent.iloc[0,1:]
# get diff 
df_prepend_diff = df_prepend_percent.iloc[:,1:].apply(lambda x: (x - data_baseline) , axis=1) 
df_prepend_diff = df_prepend_diff.round(3)
df_prepend_diff.insert(0, column='bgp', value=df_prepend_percent['bgp'] )
df_prepend_diff.head(3)

# D) get max/min per sites
data = df_prepend_percent[~df_prepend_percent.bgp.str.contains("0x")].copy()

# find the top values
def europe_sum(line):
    return (line['CDG']+line['LHR'])
data['europe'] = data.apply(europe_sum,axis=1)
def eua_sum(line):
    return (line['MIA']+line['IAD'])
data['eua'] = data.apply(eua_sum,axis=1)

policy_max_europe = data.iloc[data.europe.idxmax()]['bgp']
policy_max_eua = data.iloc[data.eua.idxmax()]['bgp']
policy_max_br = data.iloc[data.POA.idxmax()]['bgp']
policy_max_asia = data.iloc[data.SYD.idxmax()]['bgp']

policy_min_europe = data.iloc[data.europe.idxmin()]['bgp']
policy_min_eua = data.iloc[data.eua.idxmin()]['bgp']
policy_min_br = data.iloc[data.POA.idxmin()]['bgp']
policy_min_asia = data.iloc[data.SYD.idxmin()]['bgp']

# Functions
def build_graph_for_bgp_policy(data,policy="baseline"):    
    """ 
    plot load distribution among sites
    """
    ## get current select policy
    df_bgp_policy = data[data['bgp'] == policy].T.reset_index()[1:]
    df_bgp_policy.rename(
        columns={
            df_bgp_policy.columns[1]: "count",
            df_bgp_policy.columns[0]: "site"
        }, inplace = True)
    
    # graph layout
    layout = go.Layout(
        width=590,
        height=250,
        barmode='overlay',
        margin=dict(l=50, r=0, t=20, b=20),
        showlegend=False, 
        
        # Y axis
        yaxis = dict(
         fixedrange = False,
         range = [0,100], 
         title = "nets (/24)",
         ticksuffix = "%",
         ),   
        )
    
    # graph data
    graph_data = dict(
                    type='bar',
                    name = policy,

                    x=df_bgp_policy['site'],
                    y=df_bgp_policy['count'],
                    showlegend=False,
                    hovertext="",
                    hoverinfo = "y",
                    text = df_bgp_policy['count'],
                    marker=dict(color="blue"),
                    customdata = (policy,),
                )
    
    return (go.Figure(data=graph_data, layout=layout))
    
fig_server_load = build_graph_for_bgp_policy(df_prepend_percent)
#plotly.offline.iplot(fig_server_load)

def build_sliders(data,site="LHR"):
    """
    build the sliders and availabel steps for each site
    """

    id = "slider-{}".format(site)
    print (id)
    
    # by convention, site name"0x" means that this site was been disabled 
    data = data[~data.bgp.str.contains("0x")]
    marks = dict()
    value_baseline = data.loc[df_prepend_percent.bgp=='baseline',site].values[0]
    marks[-50] = {'label': '-', 'style': {'color': '#000000',"font-size": "14px"}}
    marks[50] = {'label': '+', 'style': {'color': '#000000', "font-size": "14px"}}
    

    for value in data[site].sort_values():
        label = " "
        marks[value] = label 
    
    slider =  dcc.Slider(
            id=id,
            min=-50,
            max=50,
            step=None,
            vertical="True",
            verticalHeight = "180",
            marks=marks,
            value=value_baseline,
            included=False,
        className="range-field w-75") 
    return html.Div([slider])

slider =  build_sliders(df_prepend_diff)

def define_label(policy):
    """
    build label describing the policy selected
    """
    header_label = "Site Load Distribution {}".format(policy)
    print (policy)
    if not (policy):
        policy = "baseline"
        header_label = "Site Load Distribution {}".format(policy)
        return (header_label,"")
    
    info_label = policy
    if (policy=="baseline"):
        info_label = "Default Anycast configuration"
    elif "0x" in policy:
        info_label = "Remove prefix announcement on CDG"
        
    elif "-" not in policy:
        info_label = " {} prepend(s) on site {}.".format(policy.split("x")[0],policy.split("x")[1])
    elif "-" in policy:
        nodes = ["CDG","LHR","IAD","SYD","POA", "MIA"]
        nodes.remove(policy.split("x")[1])
        list_nodes = ', '.join([str(elem) for elem in nodes]) 
        num_prepends = policy.split("x")[0].replace("-","")
        info_label = " {} prepend(s) on sites {}.".format(num_prepends,list_nodes)
    
    return (header_label,info_label)

## Website components
# tob bar
NAVBAR = dbc.Navbar(
    children=[
        html.A(
            dbc.Row(
                [
                    dbc.Col(
                        dbc.NavbarBrand("SAND Project - The BGP Anycast Playground",
                                        className="ml-2")
                    ),
                ],
                align="center",
                #no_gutters=True,
                className="g-0"
            ),
            href="http://sand-project.nl/",
        )
    ],
    color="dark",
    dark=True,
    sticky="top",
)

# sliders row
row_sliders = dbc.Col(
    [
        html.Div([
            html.Span("CDG"),
            build_sliders(df_prepend_diff, "CDG"),
        ], className="float-center p-4 border bg-light d-inline-block"),

        html.Div([
            html.Span("IAD"),
            build_sliders(df_prepend_diff, "IAD"),
        ], className="float-center p-4  border bg-light d-inline-block"),

        html.Div([
            html.Span("LHR"),
            build_sliders(df_prepend_diff, "LHR"),
        ], className="float-center p-4  border bg-light d-inline-block"),

        html.Div([
            html.Span("MIA"),
            build_sliders(df_prepend_diff, "MIA"),
        ], className="float-center p-4  border bg-light d-inline-block"),

        html.Div([
            html.Span("POA"),
            build_sliders(df_prepend_diff, "POA"),
        ], className="float-center p-4  border bg-light d-inline-block"),

        html.Div([
            html.Span("SYD"),
            build_sliders(df_prepend_diff, "SYD"),
        ], className="float-center p-4  border bg-light d-inline-block"),

    ], className="ml-2 pl-5",
)

# dropdown menu
def build_dropdown():

    return (dcc.Dropdown(
        id='dropdown', multi=False, clearable=True, style={"marginBottom": 10, "font-size": 12},
        options=[
            {'label': 'Bring traffic to Europe', 'value': policy_max_europe},
            {'label': 'Bring traffic to USA', 'value': policy_max_eua},
            {'label': 'Bring traffic to South America', 'value': policy_max_br},
            {'label': 'Bring traffic to Asia', 'value': policy_max_asia},
            {'label': 'Get rid of traffic in Europe', 'value': policy_min_europe},
            {'label': 'Get rid of traffic in USA', 'value': policy_min_eua},
            {'label': 'Get rid of traffic in South America', 'value': policy_min_br},
            {'label': 'Get rid of traffic in Asia', 'value': policy_min_asia},
            {'label': 'Remove node CDG', 'value': "0xCDG"},
            {'label': 'Remove node IAD', 'value': "0xIAD"},
            {'label': 'Remove node LHR', 'value': "0xLHR"},
            {'label': 'Remove node MIA', 'value': "0xMIA"},
            {'label': 'Remove node POA', 'value': "0xPOA"},
            {'label': 'Remove node SYD', 'value': "0xSYD"},
        ],
        placeholder="Select a policy",
        value="baseline",
    )
    )

build_dropdown()

# modal component (alert message)
def build_modal(value="baseline"):

    modal = dbc.Modal([
        dbc.ModalHeader("The following BGP policy will be applied:"),
        dbc.ModalBody(
            [
                html.Div(id='modal-content')
            ]),

        dbc.ModalFooter(
            dbc.Button("Close", id="close", className="ml-auto")
        ),
    ],
        id="modal",
    )
    return modal


build_modal()

# initializing the APP
app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])

# website left column
# LEFT_COLUMN = dbc.Jumbotron(
#     [
#         dbc.Col(html.Img(src=app.get_asset_url("sand-logo.png"), height="35px",
#                          className="mr-4 pr-2")),

#         html.H6("Select desired goal", style={
#                 "marginTop": 50}, className="lead"),
#         html.P(
#             "(You can use the dropdown and see the load change on the graph.)",
#             style={"fontSize": 10, "font-weight": "lighter"},
#         ),
#         build_dropdown(),
#         html.Div(
#             dbc.Button("Deploy", color="success", block=True, id="button")
#         ),

#         # store value
#         html.Div(id='bgp-value', style={'display': 'none'}),
#         build_modal()
#     ],
# )
LEFT_COLUMN = dbc.Container(
    [
        dbc.Row(
            [
                dbc.Col(html.Img(src=app.get_asset_url("sand-logo.png"), height="35px", className="mr-4 pr-2")),
                dbc.Col(
                    [
                        html.H6("Select desired goal", className="lead"),
                        html.P(
                            "(You can use the dropdown and see the load change on the graph.)",
                            style={"fontSize": 10, "font-weight": "lighter"},
                        ),
                        build_dropdown(),
                        #dbc.Button("Deploy", color="success", block=True, id="button"),
                        dbc.Button("Deploy", color="success", id="button", className="btn-block"),
                    ],
                    width=8,  # Adjust width as needed
                ),
            ],
            className="align-items-center",  # Align items vertically in the row
            style={"marginTop": 50},  # Adjust top margin as needed
        ),
        html.Div(id='bgp-value', style={'display': 'none'}),
        build_modal(),
    ],
    fluid=True,  # Use fluid layout
    className="py-3",
)

# Toast component - label
toast = dbc.Toast(
    [
        html.P("This is the default configuration",
               id="policy-description", className="mb-0")
    ],
    header="BGP Policy Description",
    is_open=True,
    dismissable=True,
    icon="danger",
)

# Central graphic component
card_content = [
    dbc.Col(
        dbc.Card(
            [
                dbc.CardHeader("Site Load Distribution",
                               id="policy-description-header"),
                dbc.CardBody(
                    [
                        dcc.Graph(id="serve-load-graph", figure=fig_server_load,
                                  config={'displayModeBar': False}),
                        row_sliders,
                    ]
                ),
            ], color="white"
        )
    )
]

# html body
BODY = dbc.Container(
    [
        dbc.Row(
            [
                dbc.Col(LEFT_COLUMN, md=3, align="top",
                        width={"size": 0, "offset": 0}),

                dbc.Col(dbc.Container(
                    [
                        dbc.Row(card_content),
                    ], style={"padding": "0px 0px 00px 0px"}), md=8),
            ],

        ),
        dbc.Row(dbc.Col([toast], style={"padding": "0px 0px 20px 0px"}, md=3))
    ],
    className="p-3",
)

# APP
app.layout = html.Div(children=[NAVBAR, BODY])


## callback function - responsible for interaction

#### SLIDER CDG
@app.callback(
    [
     Output("slider-IAD", "value"),
     Output("slider-LHR", "value"),
     Output("slider-MIA", "value"),
     Output("slider-POA", "value"),
     Output("slider-SYD", "value"),
     Output("serve-load-graph", "figure"),
     Output("policy-description-header", "children"),
     Output("policy-description", "children"),
     Output("modal-content", "children"),
    ],
    [Input('slider-CDG', 'value')],
)
def callback_function(value): 
    source_node = "CDG"
    results = []
    nodes = ['IAD', 'LHR', 'MIA', 'POA', 'SYD']
    
    max_slider_value = 50
    min_slider_value = -50
    
    # min_slider_value is a constant that define "node was removed"
    if (value==min_slider_value):
        print ("remove node {}".format(source_node))
        string_regex = "0x{}".format(source_node)
        policy = string_regex
        df_aux = df_prepend_diff[['bgp', 'IAD', 'LHR', 'MIA', 'POA', 'SYD']]
        results = df_aux[df_aux.bgp.str.contains(string_regex)].iloc[0,1:].tolist()
        
    else:
        # force max value (50) to be rewrited to the max available value
        if (value==max_slider_value):
            value = df_prepend_diff.iloc[df_prepend_diff.CDG.idxmax()]['CDG'].tolist()

        for node in nodes:
            try:
                new_value = df_prepend_diff.loc[df_prepend_diff[source_node]==value,[node]].values[0][0]
            except:
                print ("this value has not found on diff, so this is the maximum")
                new_value = 0

            results.append(new_value)
        try:  
            policy = df_prepend_diff.loc[df_prepend_diff[source_node]==value,'bgp'].values[0]
        except:
            policy = 0

    
    # new figure 
    if (policy):
        fig = build_graph_for_bgp_policy(df_prepend_percent,policy)
    else:
        fig = build_graph_for_bgp_policy(df_prepend_percent)
    results.append(fig)
   
    (label_header, label_info) = define_label(policy)
    
    results.append(label_header) 
    results.append("Policy: "+label_info) 
    results.append(label_info) 
    return (results)


#### Dropdown
@app.callback(
    [
     Output("slider-CDG", "value"),
    ],
    [Input('dropdown', 'value')],
)
def callback_function(policy): 
    try:
        new_value = (df_prepend_diff.loc[df_prepend_diff.bgp==policy,'CDG'].values[0])
    except:
        new_value = "baseline"
    return ([new_value])

#### Button
@app.callback(
    Output("modal", "is_open"),
    [Input("button", "n_clicks"), 
     Input("close", "n_clicks")],
    [State("modal", "is_open")],
)
def toggle_modal(n1, n2, is_open):
    if n1 or n2:
        return not is_open
    return is_open

if __name__ == '__main__':
    app.run_server(debug=False, host="0.0.0.0", port=12445)
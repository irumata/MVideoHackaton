from tomita import TomitaParser
import pandas as pd
import numpy as np

tomita = TomitaParser("./tomita-linux64", 
                          "./config.proto", debug=False)

def text_parse(text):
    facts, leads = tomita.run(text)
    result = []
    for x in facts:
        result.append([x['fact_main'], x['fact_left'], x['fact_right']])
    
    dfr = pd.DataFrame([x[0] for x in result], columns=['Noun'])
    dfr['Text'] = [x[1] + ' ' + x[0] if len(x[1]) else x[0] + ' ' + x[2] for x in result]
    
    return dfr.values
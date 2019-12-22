from flask import Flask,render_template,request
from flask_bootstrap import Bootstrap
from flask_datepicker import datepicker

import os
import sqlite3
import json
import time
from datetime import datetime

app = Flask(__name__)
Bootstrap(app)
datepicker(app)

conn = sqlite3.connect('database.db',check_same_thread = False)
c = conn.cursor()
    
@app.route('/post_data',methods=['GET','POST'])
def post_data():
    data = {}
    data['heart'] = request.values['heart']
    # data['heart']=0
    data['step'] = request.values['step']
    data['battery'] = request.values['battery']
    data['charging'] = request.values['charging']
    data['latitude'] = request.values['latitude']
    data['longitude'] = request.values['longitude']
    data['height'] = request.values['height']
    data['h'] = request.values['h']
    data['m'] = request.values['m']
    data['s'] = request.values['s']
    data['s_num'] = request.values['s_num']
    payload = """INSERT INTO linkit_one_data (timestamp,heart,step,battery,charging,latitude,longitude,height)
                VALUES ({},{},{},{},{},{},{},{})""".\
                format(int(time.time()),data['heart'],data['step'],data['battery'],data['charging'],data['latitude'],data['longitude'],data['height'])

    c.execute(payload)
    conn.commit()
    print(data) 
    return 'meow'

@app.route('/get_data', methods = ['POST'])
def get_data():
    date = request.form['date']

    timeArray = time.strptime(date, "%m/%d/%Y")
    startTimeStamp = int(time.mktime(timeArray))
    endTimeStamp = startTimeStamp + 86400

    # print(startTimeStamp)
    # print(endTimeStamp)
    payload = "SELECT * FROM linkit_one_data where timestamp >= " + str(startTimeStamp) + " and timestamp <= " + str(endTimeStamp)
    # payload = """SELECT * FROM linkit_one_data where Date(timestamp) = '""" + str(date) + "'"
    # payload = """SELECT * FROM linkit_one_data""" 
    # print(payload)
    c.execute(payload)
    d = c.fetchall()
    data = []
    calc_data = {}
    for _ in range(24):
        calc_data[str(_)] = 0
    for i in d:
        _datetime = datetime.fromtimestamp(int(i[1])).strftime('%Y-%m-%d %H:%M:%S')
        t = {
            'timestamp': _datetime,
            'heart':i[2],
            'step':i[3],
            'battery':i[4],
            'charging':i[5],
            'latitude':i[6],
            'longitude':i[7],
            'height':i[8]
        }
        print(_datetime, int(_datetime[14:16]))
        calc_data[str(int(_datetime[11:13]))] = i[2]
        data.append(t)
    
    data = [calc_data] + [{'distance' : '8.63', 'duration': '52:03', 'pace': "8'50\"", "Calor":"352", "heartRate": "86"}] + data 
    print(calc_data)
    return json.dumps(data)


@app.route('/')
def index():
    return render_template('index.html')

if __name__ == '__main__':


    app.run(debug = True, host = '0.0.0.0', port = 8891)


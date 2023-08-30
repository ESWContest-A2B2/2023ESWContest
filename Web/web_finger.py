from flask import Flask, send_from_directory
from flask.templating import render_template
from Data import Finger

app = Flask(__name__)


@app.route('/')
def webFinger():
	webList = Finger().getFinger(); #Data 파일 안의 Finger class에서 getFinger를 실행하여 저장한다.
	return render_template("WebFinger.html", webList=webList) #html을 적용시켜 웹페이지에 표현한다.

if __name__ =="__main__":
        app.run(host='0.0.0.0') #모든 ip접속 가능


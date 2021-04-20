from flask import Flask
from flask import request
from flask import Response
from flask import redirect
from flask import url_for
from flask import make_response
from flask import render_template_string

import jwt

TABLE_ROW = """<tr>
	<td style='border: 1px solid'>{}</td>
	<td style='border: 1px solid'>{}</td>
	<td style='border: 1px solid'>{}</td>
	<td style='border: 1px solid'>{}</td>
</tr>
"""
TEMPLATE = """<html>
<body>
  <h1>Fleet inventory</h1>
  <p>
  	<b>{}</b>
  </p>
  <p>
	  <form method="post">
		<label for="search">Search (PRO)</label>
		<input name="search" id="search" placeholder="' OR '1'='1" required>
		<input type="submit" value="Search">
	  </form>
	  Filter: {}
  </p>
  <p>
  	<table>
  		<thead>
  			<tr>
  				<td><b>Manufacturer</b></td>
  				<td><b>Model</b></td>
  				<td><b>Year</b></td>
  				<td><b>hp</b></td>
			</tr>
		</thead>
  		<tbody>
			{}
		</tbody>
	<table>
  </p>
</body>
</html>"""

class Car:
	def __init__(self, manufacturer, model, year, hp):
		self.manufacturer = manufacturer
		self.model = model
		self.year = year
		self.hp = hp
		
	def filter(self, query):
		return \
		query in self.manufacturer or \
		query in self.model or \
		query in self.year or \
		query in self.hp
		
	def row_template(self):
		return TABLE_ROW.format(self.manufacturer, self.model, self.year, self.hp)

CARS = [
	Car("Toyota", "Yaris", "2018", "100"),
	Car("Audi", "80", "1990", "110"),
	Car("Daimler", "Double-Six", "1985", "120"),
	Car("Facel", "vega", "1960", "95"),
	Car("Maserati", "Bora", "1976", "102"),
	Car("BMW", "X5 Mkl", "2004", "140"),
	Car("Bentley", "Continental GT Mkl", "2009", "130"),
	Car("Morgan", "Plus 8", "1999", "112"),
	Car("Skoda", "S11OR", "1970", "92"),
	Car("Hispano-Suiza", "H6", "1930", "85"),
	Car("Riley", "MPH", "1934", "89"),
	Car("Bristol", "400", "1935", "82")
]
with open('jwt-rs256.key', 'r') as fp:
	RS256_PRIV_KEY = fp.read()
with open('jwt-rs256.pub', 'r') as fp:
	RS256_PUB_KEY = fp.read()
app = Flask(__name__, instance_relative_config=True)

@app.route("/robots.txt", methods=["GET", "POST"])
def robots():
	return Response("/client", mimetype="text/plain")
	
@app.route("/public", methods=["GET", "POST"])
def public():
	return redirect(url_for('client'))
	
@app.route("/client", methods=["GET", "POST"])
def client():
	return Response(RS256_PUB_KEY, mimetype="text/plain")
			
@app.route("/", methods=["GET", "POST"])
def index():
	errors = ''
	search = ''
	car_details = CARS
	
	if "session" in request.cookies:
		jwtauth = request.cookies.get("session")
	else:
		jwtauth = jwt.encode({'user': 'guest', 'pro': False}, RS256_PRIV_KEY, algorithm='RS256')
		
	if "search" in request.values:
		try:
			claims = jwt.decode(jwtauth, RS256_PUB_KEY, algorithms=['RS256', 'HS256'])
			if claims['pro'] != True:
				raise ValueError()
			search = request.values["search"]
			car_details = [i for i in car_details if i.filter(search)]
		except:
			errors = 'Search is available only to PRO users'

	rows = ''.join([i.row_template() for i in car_details])
	template = TEMPLATE.format(errors, search, rows)
	response = make_response(render_template_string(template))
	response.set_cookie("session", jwtauth)
	return response


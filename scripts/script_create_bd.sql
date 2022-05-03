CREATE TABLE IF NOT EXISTS station (
	id INTEGER PRIMARY KEY,
	settlement VARCHAR(100) NOT NULL,
	latitude REAL NOT NULL CHECK (latitude <= 180 AND latitude >= -180),
	longitude REAL NOT NULL CHECK (longitude <= 180 AND longitude >= -180)
);

CREATE TABLE IF NOT EXISTS order_status (
	id INTEGER PRIMARY KEY,
	payment_status VARCHAR(50),
	execution_status VARCHAR(50),
	execution_date TIMESTAMP
);

CREATE TABLE IF NOT EXISTS customer_company (
	id INTEGER PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	contact_number VARCHAR(50) NOT NULL,
	contact_mail VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS locomotive (
	id INTEGER PRIMARY KEY,
	weight_limit INTEGER NOT NULL CHECK (weight_limit > 0),
	type VARCHAR(100) NOT NULL,
	maintenance_date DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS railway_carriage (
	id INTEGER PRIMARY KEY,
	weight_limit INTEGER NOT NULL CHECK (weight_limit > 0),
	type VARCHAR(100) NOT NULL,
	maintenance_date DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS composition_of_carriages (
	id INTEGER PRIMARY KEY,
	locomotive INTEGER REFERENCES locomotive(id) ON DELETE CASCADE,
	railway_carriage INTEGER REFERENCES railway_carriage(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS position (
	id INTEGER PRIMARY KEY,
	title VARCHAR(100) NOT NULL,
	salary INTEGER NOT NULL CHECK (salary > 0),
	responsibilities VARCHAR(200) NOT NULL
);

CREATE TABLE IF NOT EXISTS worker (
	id INTEGER PRIMARY KEY,
	full_name VARCHAR(100) NOT NULL,
	position VARCHAR(100) NOT NULL,
	passport VARCHAR(100) NOT NULL,
	salary INTEGER NOT NULL CHECK (salary > 0),
	work_experience DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS cargo_order (
	id INTEGER PRIMARY KEY,
	railway_carriage INTEGER REFERENCES railway_carriage(id) ON DELETE CASCADE,
	order_status INTEGER REFERENCES order_status(id) ON DELETE CASCADE,
	start_station INTEGER REFERENCES station(id) ON DELETE CASCADE,
	end_station INTEGER REFERENCES station(id) ON DELETE CASCADE,
	driver INTEGER REFERENCES worker(id) ON DELETE CASCADE,
	customer_company INTEGER REFERENCES customer_company(id) ON DELETE CASCADE,
	price INTEGER NOT NULL CHECK (price > 0),
	cargo_weight INTEGER NOT NULL CHECK (cargo_weight > 0),
	cargo_name VARCHAR(50) NOT NULL,
	cargo_description VARCHAR(200) NOT NULL,
	order_date TIMESTAMP NOT NULL
);

CREATE TABLE IF NOT EXISTS loading_brigade (
	id INTEGER PRIMARY KEY,
	cargo_order INTEGER REFERENCES cargo_order(id) ON DELETE CASCADE,
	worker INTEGER REFERENCES worker(id) ON DELETE CASCADE
);

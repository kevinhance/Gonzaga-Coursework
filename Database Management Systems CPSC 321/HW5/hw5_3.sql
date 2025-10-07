DROP TABLE IF EXISTS table1;
DROP TABLE IF EXISTS table2;

CREATE TABLE table2(
    company_id INT UNSIGNED,
    company_name VARCHAR(40),
    company_city VARCHAR(40),
    PRIMARY KEY(company_id)
);

CREATE TABLE table1(
    item_id INT UNSIGNED,
    item_name VARCHAR(30),
    item_price FLOAT,
    company_id INT UNSIGNED,
    FOREIGN KEY (company_id) REFERENCES table2 (company_id),
    PRIMARY KEY (item_id)
);

INSERT INTO table2 VALUES (1001, 'Apple', 'San Francisco');
INSERT INTO table2 VALUES (1002, 'Microsoft', 'Redmond');
INSERT INTO table2 VALUES (1003, 'Uber', 'Los Angeles');
INSERT INTO table2 VALUES (1004, 'Lyft', 'Chicago');

INSERT INTO table1 VALUES (10001, 'Black Airpods', 129.99, 1001);
INSERT INTO table1 VALUES (10024, 'Windows 10 Professional', 149.99, 1002);
INSERT INTO table1 VALUES (10157, 'Uber T-shirt', 19.95, 1003);
INSERT INTO table1 VALUES (10402, 'Lyft Baseball Cap', 21.99, 1004);

SELECT * FROM table1;
SELECT * FROM table2;

SELECT * FROM table1 NATURAL JOIN table2;

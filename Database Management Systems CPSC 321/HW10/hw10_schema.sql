DROP TABLE IF EXISTS Employee;

CREATE TABLE Employee(
    employee_id INTEGER UNSIGNED,
    salary INTEGER UNSIGNED,
    title VARCHAR(50),
    PRIMARY KEY (employee_id)
);

CREATE INDEX salary ON Employee(title, salary);
/*SELECT * FROM Employee WHERE title = 'engineer' and salary < 50000;*/
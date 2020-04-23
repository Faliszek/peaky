create table p_users (
    id SERIAL PRIMARY KEY, 
    email varchar(255) not  null, 
    password text not null);


INSERT INTO p_users (email, password)
VALUES ('admin@test.com', '$2y$06$co364YH/v6nNtQx8S9Xu5egwZIkmfAzH5z13g0ieYk/q7ZisZI.1u');


INSERT INTO p_users (email, password)
VALUES ('user@test.com', '$2y$06$co364YH/v6nNtQx8S9Xu5egwZIkmfAzH5z13g0ieYk/q7ZisZI.1u');
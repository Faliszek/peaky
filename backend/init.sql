CREATE TABLE IF NOT EXISTS p_users  (
    id SERIAL PRIMARY KEY, 
    email varchar(255) not  null, 
    password text not null,
    archived boolean not null,
    created_at timestamp not null,
    updated_at timestamp not null
);

CREATE TABLE IF NOT EXISTS p_conservations  (
    id SERIAL PRIMARY KEY, 
    users text[]
    messages text[]
    created_at timestamp not null,
    updated_at timestamp not null
);



INSERT INTO p_users (email, password, archived, created_at, updated_at)
VALUES ('admin@test.com', '$2y$06$co364YH/v6nNtQx8S9Xu5egwZIkmfAzH5z13g0ieYk/q7ZisZI.1u', FALSE, current_timestamp, current_timestamp);


INSERT INTO p_users (email, password, archived, created_at, updated_at)
VALUES ('user@test.com', '$2y$06$co364YH/v6nNtQx8S9Xu5egwZIkmfAzH5z13g0ieYk/q7ZisZI.1u', FALSE, current_timestamp, current_timestamp);
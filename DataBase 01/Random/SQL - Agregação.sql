DROP TABLE IF EXISTS MONITORA;
DROP TABLE IF EXISTS FINANCIA;

DROP TABLE IF EXISTS PROJETOS;
DROP TABLE IF EXISTS DEPARTAMENTOS;
DROP TABLE IF EXISTS FUNCIONARIOS;

CREATE TABLE FUNCIONARIOS (
    cpf CHAR(11), /* CHAR guarda um tamanho fixo */
    nome VARCHAR (100), /* VARCHAR qualquer tamanho até um valor máximo */
    vaga INTEGER,
    PRIMARY KEY (cpf)
); 

CREATE TABLE PROJETOS (
    id INTEGER,
    inicio DATE,
    orcamento INTEGER,
    PRIMARY KEY (id)
); 

CREATE TABLE DEPARTAMENTOS (
    id INTEGER,
    nome VARCHAR(100),
    orcamento INTEGER,
    PRIMARY KEY (id)
); 

CREATE TABLE FINANCIA (
    id_projeto INTEGER,
    id_departamento INTEGER,
    desde DATE,
    FOREIGN KEY (id_projeto) REFERENCES PROJETOS(id),
    FOREIGN KEY (id_departamento) REFERENCES DEPARTAMENTOS(id),
    PRIMARY KEY (id_projeto, id_departamento)
);

CREATE TABLE MONITORA ( /* Relacionamento N->N entre FINANCIA e MONITORA */
    cpf CHAR(11),
    id_projeto INTEGER,
    id_departamento INTEGER,
    ate DATE,
    FOREIGN KEY (cpf) REFERENCES FUNCIONARIOS(cpf),
    FOREIGN KEY (id_projeto, id_departamento) REFERENCES FINANCIA (id_projeto, id_departamento),
    PRIMARY KEY (cpf, id_projeto, id_departamento)
);

INSERT INTO FUNCIONARIOS (cpf, nome, vaga) VALUES ('04402159199', 'Breno Farias', 1);
INSERT INTO FUNCIONARIOS (cpf, nome, vaga) VALUES ('22222222222', 'Manoel Campos', 2);
INSERT INTO FUNCIONARIOS (cpf, nome, vaga) VALUES ('33333333333', 'Marcia Farias', 3);
INSERT INTO FUNCIONARIOS (cpf, nome, vaga) VALUES ('44444444444', 'Amanda Farias', 4);
SELECT * FROM FUNCIONARIOS;

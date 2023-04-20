CREATE TABLE GENERO(
    descricao VARCHAR(50) PRIMARY KEY
);

CREATE TABLE ATOR(
    nomeReal VARCHAR(100) PRIMARY KEY,
    sexo CHAR(1)
);

CREATE TABLE FILME(
    id INTEGER PRIMARY KEY,
    nome VARCHAR(100),
    anoEstreia INTEGER,
    descricaoGenero VARCHAR(50) NOT NULL,
    FOREIGN KEY (descricaoGenero) REFERENCES GENERO(descricao)
);

CREATE TABLE DVD(
    id INTEGER PRIMARY KEY,
    idFilme INTEGER NOT NULL,
    FOREIGN KEY (idFilme) REFERENCES FILME(id)
);

CREATE TABLE ELENCO(
    idFilme INTEGER,
    nomeAtor VARCHAR(100),
    PRIMARY KEY (idFilme, nomeAtor),
    FOREIGN KEY (idFilme) REFERENCES FILME(id),
    FOREIGN KEY (nomeAtor) REFERENCES ATOR(nomeReal)
);

-- Exercício 1 - Escreva em SQL uma consulta que liste todos os filmes, juntamente com os ids dos DVDs, do gênero "Drama".
SELECT F.nome, D.id
FROM FILME F, DVD D
WHERE F.descricaoGenero = 'Drama';

-- Exercício 2 - Escreva em SQL uma consulta que exiba os gêneros sem repetição dos filmes estreados em 2020 com a participação do ator "Severino".
SELECT DISTINCT F.descricaoGenero
FROM FILME F
WHERE F.anoEstreia = 2020 AND F.id IN ( SELECT E.idFilme
								FROM ELENCO E
                                WHERE E.nomeAtor = 'Severino'
);

-- Exercício 3 - Escreva em SQL uma consulta que exiba a quantidade de DVDs por filmes.
SELECT COUNT(D.id)
FROM DVD D
WHERE D.idFilme IN (SELECT DISTINCT F.id
					FROM FILME F
);

-- Exercício 4 - Escreva em SQL uma consulta que liste os filmes estreados em 2020, que não tiveram a participação do ator "Severino".
SELECT F.nome, F.id
FROM FILME F
WHERE F.anoEstreia = 2020 AND F.id IN ( SELECT E.idFilme
										FROM ELENCO E
										WHERE E.nomeAtor <> 'Severino'
);

-- Exercício 5 - Escreva em SQL uma consulta que selecione os gêneros e a quantidade de filmes que foram estreados em 2020.
SELECT DISTINCT F.descricaoGenero, COUNT(F.id)
FROM FILME F
GROUP BY F.anoEstreia
HAVING F.anoEstreia = 2020;

-- Exercício 6 - Escreva em Álgebra Relacional uma consulta que liste os atores que participaram de filmes em 2020, mas não em 2019.





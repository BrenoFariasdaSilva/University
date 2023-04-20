-- Selecione todos alunos que são menores do que 20 anos e são do nível 'JR'

-- Selecione os professores que são do departamento  68

-- Selecione os alunos que se matricularam em curso de 'Database Systems'

-- Selecione os nomes dos professores que ministraram algum curso na sala '20 AVW'

-- Selecione o nivel dos alunos (sem repetição) que cursaram algum curso na sala '20 AVW'

-- Liste o nome do alunos e o nome da formação cuja formação contenha a string 'cie'

-- Conte o número de alunos.

-- Quantas matrículas há no curso com nome 'Database Systems'

-- Selecione o nome de todos os professores dos departamentos 68 e 12.

-- Selecione o nome dos professores que deram aulas no curso com 'Database Systems' ou são do departamento 68.

-- Selecione o número dos alunos com formação 'Computer Science' ou que fizeram o curso de 'Database Systems'.

-- CREATE DATABASE list3DataBase01;

USE list3DataBase01; 

DROP TABLE IF EXISTS MATRICULADO;
DROP TABLE IF EXISTS ALUNO;
DROP TABLE IF EXISTS CURSO;
DROP TABLE IF EXISTS PROFESSOR;

CREATE TABLE ALUNO( 	
    nroAlun INTEGER PRIMARY KEY, 	
    nomeAlun VARCHAR (30), 	
    formacao VARCHAR (25), 	
    nivel VARCHAR(2), 	
    idade INTEGER	
); 

CREATE TABLE PROFESSOR(
	idProf INTEGER PRIMARY KEY, 	
	nomeProf VARCHAR (30), 	
	idDepto INTEGER	
);

CREATE TABLE CURSO( 	
	nome VARCHAR(40) PRIMARY KEY, 	
	horario VARCHAR(20), 	
	sala VARCHAR (10), 	
	idProf INTEGER, 	
	FOREIGN KEY(idProf) REFERENCES PROFESSOR(idProf)	
); 

CREATE TABLE MATRICULADO( 	
	nroAlun INTEGER, 	
	nomeCurso varchar(40), 	
	PRIMARY KEY (nroAlun, nomeCurso), 	
	FOREIGN KEY (nroAlun) REFERENCES ALUNO(nroAlun), 
	FOREIGN KEY (nomeCurso) REFERENCES CURSO(nome) 	
);
INSERT INTO ALUNO(nroAlun, nomeAlun, formacao, nivel, idade) VALUES (051135593, 'Maria White', 'English', 'SR',21),  (060839453, 'Charles Harris', 'Architecture', 'SR', 22), (099354543, 'Susan Martin', 'Law', 'JR' ,20), (112348546, 'Joseph Thompson' ,'Computer Science', 'SO', 19), (115987938, 'Christopher Garcia', 'Computer Science', 'JR', 20), (132977562, 'Angela Martinez', 'History', 'SR', 20), (269734834, 'Thomas Robinson', 'Psychology', 'SO', 18), (280158572, 'Margaret Clark', 'Animal Science', 'FR', 18), (301221823, 'Juan Rodriguez', 'Psychology', 'JR', 20), (318548912, 'Dorthy Lewis', 'Finance', 'FR', 18), (320874981, 'Daniel Lee', 'Electrical Engineering', 'FR', 17), (322654189, 'Lisa Walker', 'Computer Science', 'SO', 17), (348121549, 'Paul Hall' ,'Computer Science', 'JR', 18), (351565322, 'Nancy Allen', 'Accounting', 'JR', 19), (451519864, 'Mark Young', 'Finance', 'FR', 18), (455798411, 'Luis Hernandez', 'Electrical Engineering', 'FR', 17), (462156489, 'Donald King', 'Mechanical Engineering', 'SO', 19), (550156548, 'George Wright', 'Education', 'SR', 21), (552455318, 'Ana Lopez', 'Computer Engineering', 'SR', 19), (556784565, 'Kenneth Hill', 'Civil Engineering', 'SR', 21), (567354612, 'Karen Scott', 'Computer Engineering', 'FR', 18), (573284895, 'Steven Green', 'Kinesiology',  'SO', 19), (574489456, 'Betty Adams', 'Economics', 'JR', 20), (578875478, 'Edward Baker', 'Veterinary Medicine', 'SR', 21);
INSERT INTO PROFESSOR(idProf, nomeProf, idDepto) VALUES (142519864, 'Ivana Teach',20),  (242518965, 'James Smith',68), (141582651, 'Mary Johnson',20), (011564812, 'John Williams',68), (254099823, 'Patricia Jones',68), (356187925, 'Robert Brown',12), (489456522, 'Linda Davis',20), (287321212, 'Michael Miller',12), (248965255, 'Barbara Wilson',12), (159542516, 'William Moore',33), (090873519, 'Elizabeth Taylor',11), (486512566, 'David Anderson',20),  (619023588, 'Jennifer Thomas',11),  (489221823, 'Richard Jackson',33),  (548977562, 'Ulysses Teach',20);
INSERT INTO CURSO(nome, horario, sala, idProf) VALUES ('Data Structures', 'MWF 10', 'R128', 489456522), ('Database Systems', 'MWF 12:30-1:45', '1320 DCL', 142519864),  ('Operating System Design', 'TuTh 12-1:20', '20 AVW', 489456522),   ('Archaeology of the Incas', 'MWF 3-4:15', 'R128', 248965255),  ('Aviation Accident Investigation', 'TuTh 1-2:50','Q3', 011564812),  ('Air Quality Engineering','TuTh 10:30-11:45','R15', 011564812),  ('Introductory Latin', 'MWF 3-4:15','R12', 248965255),  ('American Political Parties', 'TuTh 2-3:15','20 AVW', 619023588),  ('Social Cognition', 'Tu 6:30-8:40','R15', 159542516),  ('Perception', 'MTuWTh 3','Q3', 489221823),  ('Multivariate Analysis', 'TuTh 2-3:15' ,'R15', 489221823),  ('Patent Law','F 1-2:50','R128', 489221823),  ('Urban Economics','MWF 11','20 AVW', 489221823),  ('Organic Chemistry','TuTh 12:30-1:45','R12', 489221823),  ('Marketing Research','MW 10-11:15','1320 DCL', 489221823),  ('Seminar in American Art','M 4','R15', 489221823),  ('Orbital Mechanics','MWF 8','1320 DCL', 011564812),  ('Dairy Herd Management','TuTh 12:30-1:45','R128', 356187925),  ('Communication Networks', 'MW 9:30-10:45', '20 AVW', 141582651),  ('Optical Electronics', 'TuTh 12:30-1:45', 'R15', 254099823), ('Intoduction to Math', 'TuTh 8-9:30', 'R128', 489221823);
INSERT INTO MATRICULADO(nroAlun, nomeCurso) VALUES  (112348546,'Database Systems'),  (115987938,'Database Systems'), (348121549,'Database Systems'), (322654189,'Database Systems'), (552455318, 'Database Systems'), (455798411,'Operating System Design'), (552455318, 'Operating System Design'), (567354612, 'Operating System Design'), (112348546,'Operating System Design'), (115987938,'Operating System Design'), (322654189,'Operating System Design'), (567354612,'Data Structures'), (552455318,'Communication Networks'), (455798411,'Optical Electronics'), (301221823,'Perception'), (301221823,'Social Cognition'), (301221823,'American Political Parties'), (556784565,'Air Quality Engineering'), (099354543,'Patent Law'), (574489456,'Urban Economics');


-- Exercise 1
SELECT A.nomeAlun
FROM ALUNO A
WHERE A.nivel = 'JR' IN (SELECT M.nroAlun
					FROM MATRICULADO M
                    WHERE M.nomeCurso IN 
						( SELECT C.idProf
						  FROM CURSO C
                          WHERE C.idProf = 
                          ( SELECT P.idProf
							FROM PROFESSOR P
							WHERE P.nomeProf = 'Ivana Teach')
						)
                    );
     
-- Exercise 2     
SELECT MAX(idade)
FROM ALUNO
WHERE formacao = 'History'
	OR nroAlun in ( SELECT A.nroAlun
					FROM ALUNO A, MATRICULADO M, CURSO C, PROFESSOR P
                    WHERE A.nroAlun = M.nroAlun
						AND M.nomeCurso = C.nome
                        AND C.idProf = P.idProf
                        AND P.nomeProf = 'Ivana Teach'
    );
   
-- Exercise 3  
SELECT C.nome
FROM CURSO C
WHERE C.sala = 'R128' 
	OR C.nome IN ( SELECT M.nomeCurso
					FROM MATRICULADO M
					GROUP BY M.nomeCurso
					HAVING COUNT(M.nroAlun) >= 5
				);
                
-- Exercise 4  
SELECT nomeAlun 
FROM Aluno A, Matriculado AS M1, Matriculado AS M2, Curso AS C1, Curso AS C2 
WHERE A.nroAlun = M1.nroAlun
    AND M1.nroAlun = M2.nroAlun
    AND M1.nomeCurso <> M2.nomeCurso
    AND M1.nomeCurso = C1.nome
    AND M2.nomeCurso = C2.nome
    AND C1.horario =  C2.horario;
    
-- Exercise 5
SELECT P.nomeProf
FROM professor AS P
WHERE NOT EXISTS ((SELECT DISTINCT C.sala
				   FROM CURSO)                      
				   EXCEPT                                                 
				   (SELECT DISTINCT C.sala 
                   FROM CURSO C
                   WHERE C.idProf = P.idProf)
);
                   
-- Exercise 6  
SELECT P.nomeProf
FROM professor AS P
WHERE P.idProf IN ( SELECT C.nome
					FROM CURSO C
					WHERE C.nome IN ( SELECT M.nomeCurso
									 FROM MATRICULADO M
									 GROUP BY M.nroAlun
									 HAVING COUNT(M.nroAlun) < 5
									)
				);
                
-- Exercise 7 
SELECT A.nivel, AVG(A.idade)
FROM ALUNO AS A
GROUP BY A.nivel;

-- Exercise 8 
SELECT A.nivel, AVG(A.idade)
FROM ALUNO AS A
GROUP BY A.nivel
HAVING A.nivel <> 'JR';

-- Exercise 9 
SELECT A.nivel, AVG(A.idade)
FROM PROFESSOR AS P
GROUP BY A.nivel
HAVING A.nivel <> 'JR';



                
                
			
--DJ Wiley
--A01099945

--Constraint 1
--The default birthState is "Utah".
ALTER TABLE master
        ALTER COLUMN birthState DROP DEFAULT,
        ALTER COLUMN birthState SET DEFAULT "Utah";

--Test Constraint 1
INSERT INTO master (birthState)
        VALUES(DEFAULT);

--Constraint 2
--In the Teams table, the number of wins (W) and losses (L) must equal the number of games (G).
ALTER TABLE teams
       ADD CONSTRAINT games CHECK(w+l == g);

--test constraint 2
INSERT INTO teams (w,l,g)
       VALUES(20, 20, 50);
--Test Constraint 2

--Constraint 3
-- If a player wins the MVP, WS MVP, and a Gold Glove in the same season, they are automatically inducted into the Hall of Fame.
CREATE OR REPLACE FUNCTION hof() RETURNS TRIGGER AS '
       BEGIN
                WITH awrd AS (
                        SELECT masterid, awardid, yearid, row_number() OVER (PARTITION BY masterid, yearid ORDER BY yearid) AS awrds
                        FROM awardsplayers
                        WHERE awardid = $$Gold Glove$$ OR awardid = $$Most Valuable Player$$ OR awardid = $$World Series MVP$$
                ), mid AS (
                        SELECT DISTINCT ON (a.masterid) a.masterid, a.yearid
                        FROM awrd AS a
                        JOIN awrd AS b ON (a.masterid = b.masterid AND b.yearid = a.yearid AND a.awardid != b.awardid)
                        JOIN awrd AS c ON (a.masterid = c.masterid AND c.yearid = a.yearid AND c.awardid != a.awardid AND c.awardid != b.awardid)
                        WHERE (a.awrds >= 3)
                )
                INSERT INTO halloffame (masterid, yearid)
                        SELECT masterid, yearid FROM mid WHERE (masterid NOT IN (SELECT masterid FROM halloffame));
                RETURN NEW;
        END;

' LANGUAGE plpgsql;

CREATE TRIGGER hall
        AFTER INSERT OR UPDATE
        ON awardsplayers
        EXECUTE PROCEDURE hof();

--test Constraint 3
INSERT INTO awardsplayers (awardid, yearid, masterid)
        VALUES ('Most Valuable Player', 1994, 'NotARod');
SELECT * FROM halloffame WHERE (masterid = 'NotArod');


--Constraint 4
--All teams must have some name, i.e., it cannot be null.
ALTER TABLE teams
        ALTER COLUMN name SET NOT NULL;

--Test Constraint 4
INSERT INTO teams (name)
        VALUES(null);


--Constraint 5
-- Everybody has a unique name (combined first and last names).
ALTER TABLE master ADD CONSTRAINT uname UNIQUE(namefirst, namelast);

--Test Constraint 5
INSERT INTO master (masterID, namefirst, namelast)
        VALUES('johnJacobJingleHimerSchmitt', 'Babe', 'Ruth');

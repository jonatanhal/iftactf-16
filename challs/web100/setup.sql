-- Create the user
DROP USER web100;
CREATE USER 'web100'@'%' IDENTIFIED BY '701bab86-afc7-4543-b0fb-3276636022c2';

-- Create the database
CREATE DATABASE IF NOT EXISTS `challenges` ;

-- Create table
USE challenges;
DROP TABLE `db_web100`;
CREATE TABLE `db_web100` (
`username` char(32),
`password` char(32),
`uid` int(10) NOT NULL,
PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- update user privs
GRANT ALL PRIVILEGES ON challenges.db_web100 TO 'web100'@'%';
FLUSH PRIVILEGES;

-- Insert some data into aforementioned table
INSERT INTO challenges.db_web100 (`username`, `password`, `uid`) VALUES ('admin', 'ce31a774-5c25-4867-9404-2844ebeee8d8', 1);
COMMIT;

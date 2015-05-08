SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Table structure for table petition
--
CREATE DATABASE IF NOT EXISTS  petition;

#grant all on petition.* to kurt@localhost identified by 'kk0457';

use petition;

CREATE TABLE IF NOT EXISTS signee (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  signee_no int(11) unsigned NOT NULL,
  date date NOT NULL,
  city varchar(25) DEFAULT NULL,
  state varchar(25) DEFAULT NULL,
  country varchar(25) DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=latin1  AUTO_INCREMENT=1 ;

ALTER TABLE `signee` ADD UNIQUE ( `signee_no`);

CREATE TABLE IF NOT EXISTS comments (
  id int(11) unsigned NOT NULL AUTO_INCREMENT,
  signee_id int(11) unsigned NOT NULL,
  comments text,
  PRIMARY KEY (id),
# The foreign key could also be the signee(id), it seems.
  FOREIGN KEY fk_signee_no(signee_no)
  REFERENCES signee(signee_no) 
) ENGINE=InnoDB DEFAULT CHARSET=latin1  AUTO_INCREMENT=1 ;

ALTER TABLE `comments` ADD UNIQUE ( `signee_no`);

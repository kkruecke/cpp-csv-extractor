SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Table structure for table `petition`
--
CREATE DATABASE IF NOT EXISTS  petition;

use petition;

CREATE TABLE IF NOT EXISTS `test` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `signee_no` int(11) unsigned NOT NULL,
  `date` date NOT NULL,
#  `city` varchar(25) DEFAULT NULL,
#  `state` varchar(25) DEFAULT NULL,
#  `country` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `signee_no` (`signee_no`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1  AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `signer_info` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `signee_no` int(11) unsigned NOT NULL,
  `date` date NOT NULL,
  `city` varchar(25) DEFAULT NULL,
  `state` varchar(25) DEFAULT NULL,
  `country` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `signee_no` (`signee_no`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1  AUTO_INCREMENT=1 ;


CREATE TABLE IF NOT EXISTS `signer_comments` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `signee_no` int(11) unsigned NOT NULL,
  `comments` text,
  PRIMARY KEY (`id`),
# The foreign key could also be the signer_info(id), it seems.
  FOREIGN KEY fk_signee_no(signee_no)
  REFERENCES signer_info(signee_no) 
) ENGINE=InnoDB DEFAULT CHARSET=latin1  AUTO_INCREMENT=1 ;

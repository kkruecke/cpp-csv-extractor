SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Table structure for table `petition`
--

CREATE TABLE IF NOT EXISTS `petition` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `signee_no` int(10) unsigned NOT NULL,
  `date` date NOT NULL,
  `city` varchar(25) DEFAULT NULL,
  `state` varchar(25) DEFAULT NULL,
  `country` varchar(25) DEFAULT NULL,
  `comments` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `signee_no` (`signee_no`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
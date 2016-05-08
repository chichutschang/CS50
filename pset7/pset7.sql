-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (x86_64)
--
-- Host: 0.0.0.0    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `transaction` varchar(11) NOT NULL,
  `date_time` datetime DEFAULT NULL,
  `shares` int(11) NOT NULL,
  `symbol` varchar(11) NOT NULL,
  `price` int(11) NOT NULL,
  `user_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES ('0','2016-04-24 01:50:10',0,'SUNE',0,9),('0','2016-04-24 01:50:20',100,'SUNE',0,9),('0','2016-04-24 01:51:19',0,'DOW',53,9),('0','2016-04-24 01:51:33',1,'DOW',53,9),('BUY','2016-04-24 02:03:57',10,'MSFT',52,9),('SELL','2016-04-24 02:05:04',10,'MS',28,9),('SELL','2016-04-24 02:10:44',10,'Z',25,9),('SELL','2016-04-24 02:10:57',1,'GOOG',719,9),('SELL','2016-04-24 02:14:48',10,'AAPL',106,9),('SELL','2016-04-24 02:14:53',20,'FB',111,9),('SELL','2016-04-24 02:14:58',10,'UA',47,9),('SELL','2016-04-24 02:15:08',100,'TWTR',17,9),('SELL','2016-04-24 02:15:15',20,'MSFT',52,9),('SELL','2016-04-24 02:15:20',1,'GS',167,9),('BUY','2016-04-24 02:16:38',0,'TSLA',254,9),('SELL','2016-04-24 02:17:10',2,'TSLA',254,9),('BUY','2016-04-24 02:23:16',0,'TSLA',254,9),('SELL','2016-04-24 02:23:47',1,'TSLA',254,9),('BUY','2016-04-24 02:26:51',0,'TSLA',254,9),('BUY','2016-04-24 02:26:59',0,'GOOG',719,9),('BUY','2016-04-24 02:27:10',0,'SBUX',58,9),('SELL','2016-04-24 15:55:05',3,'GOOG',719,9),('SELL','2016-04-24 15:55:10',20,'SBUX',58,9),('SELL','2016-04-24 15:55:13',10,'TSLA',254,9),('BUY','2016-04-24 16:05:31',0,'MSFT',52,11),('SELL','2016-04-24 16:07:39',10,'MSFT',52,11),('BUY','2016-04-24 16:08:47',0,'MSFT',52,11),('SELL','2016-04-24 16:09:47',100,'MSFT',52,11),('BUY','2016-04-24 16:09:53',0,'MSFT',52,11),('SELL','2016-04-24 16:11:10',100,'MSFT',52,11),('BUY','2016-04-24 16:11:15',100,'MSFT',52,11),('BUY','2016-04-24 16:11:51',20,'GOOG',719,11),('SELL','2016-04-24 16:12:05',20,'GOOG',719,11),('SELL','2016-04-24 16:12:10',100,'MSFT',52,11);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `shares` int(11) NOT NULL,
  `symbol` varchar(11) NOT NULL,
  `user_id` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  UNIQUE KEY `symbol` (`symbol`)
) ENGINE=InnoDB AUTO_INCREMENT=114 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,10000.0000,'andi','$2y$10$c.e4DK7pVyLT.stmHxgAleWq4yViMmkwKz3x8XCo4b/u3r8g5OTnS'),(2,10000.0000,'caesar','$2y$10$0p2dlmu6HnhzEMf9UaUIfuaQP7tFVDMxgFcVs0irhGqhOxt6hJFaa'),(3,10000.0000,'eli','$2y$10$COO6EnTVrCPCEddZyWeEJeH9qPCwPkCS0jJpusNiru.XpRN6Jf7HW'),(4,10000.0000,'hdan','$2y$10$o9a4ZoHqVkVHSno6j.k34.wC.qzgeQTBHiwa3rpnLq7j2PlPJHo1G'),(5,10000.0000,'jason','$2y$10$ci2zwcWLJmSSqyhCnHKUF.AjoysFMvlIb1w4zfmCS7/WaOrmBnLNe'),(6,10000.0000,'john','$2y$10$dy.LVhWgoxIQHAgfCStWietGdJCPjnNrxKNRs5twGcMrQvAPPIxSy'),(7,10000.0000,'levatich','$2y$10$fBfk7L/QFiplffZdo6etM.096pt4Oyz2imLSp5s8HUAykdLXaz6MK'),(8,10000.0000,'rob','$2y$10$3pRWcBbGdAdzdDiVVybKSeFq6C50g80zyPRAxcsh2t5UnwAkG.I.2'),(9,10000.0000,'skroob','$2y$10$395b7wODm.o2N7W5UZSXXuXwrC0OtFB17w4VjPnCIn/nvv9e4XUQK'),(10,10000.0000,'zamyla','$2y$10$UOaRF0LGOaeHG4oaEkfO4O7vfI34B1W23WqHr9zCpXL68hfQsS3/e'),(11,20000.0000,'chichutschang','$2y$10$wHQJhP22ToH6wHGDJ9vkge.MHdoiyrX8tNLQ.0jdqxOd0gRw1e9QO');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-04-24 16:27:35

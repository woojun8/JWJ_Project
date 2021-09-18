CREATE DATABASE  IF NOT EXISTS `server11` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `server11`;
-- MySQL dump 10.13  Distrib 8.0.25, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: server11
-- ------------------------------------------------------
-- Server version	8.0.25

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `accounttable`
--

DROP TABLE IF EXISTS `accounttable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `accounttable` (
  `PID` bigint unsigned NOT NULL AUTO_INCREMENT,
  `Name` varchar(45) NOT NULL,
  `Password` varchar(45) NOT NULL,
  PRIMARY KEY (`PID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accounttable`
--

LOCK TABLES `accounttable` WRITE;
/*!40000 ALTER TABLE `accounttable` DISABLE KEYS */;
INSERT INTO `accounttable` VALUES (1,'c','c'),(2,'f','f'),(3,'a','a');
/*!40000 ALTER TABLE `accounttable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `characterdatatable`
--

DROP TABLE IF EXISTS `characterdatatable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `characterdatatable` (
  `no` bigint NOT NULL AUTO_INCREMENT,
  `PID` bigint NOT NULL,
  `Name` varchar(45) NOT NULL,
  `EndIndex` varchar(45) NOT NULL,
  `LastX` int NOT NULL,
  `LastY` int NOT NULL,
  `ATT` int NOT NULL,
  `HP` int NOT NULL,
  `MAXHP` int NOT NULL,
  `Score` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`no`),
  UNIQUE KEY `PID_UNIQUE` (`PID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `characterdatatable`
--

LOCK TABLES `characterdatatable` WRITE;
/*!40000 ALTER TABLE `characterdatatable` DISABLE KEYS */;
INSERT INTO `characterdatatable` VALUES (1,1,'c','0,0',-327,1207,10,100,100,0),(2,2,'f','0,0',420,-1761,10,100,100,0),(3,3,'a','0,0',5,-92,10,100,100,0);
/*!40000 ALTER TABLE `characterdatatable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `friendtable`
--

DROP TABLE IF EXISTS `friendtable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `friendtable` (
  `no` int NOT NULL AUTO_INCREMENT,
  `PID` bigint DEFAULT NULL,
  `PName` varchar(45) NOT NULL,
  `FID` bigint DEFAULT NULL,
  `FName` varchar(45) NOT NULL,
  PRIMARY KEY (`no`),
  UNIQUE KEY `PID_FID` (`PID`,`FID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `friendtable`
--

LOCK TABLES `friendtable` WRITE;
/*!40000 ALTER TABLE `friendtable` DISABLE KEYS */;
INSERT INTO `friendtable` VALUES (5,2,'f',1,'c');
/*!40000 ALTER TABLE `friendtable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `itemtable`
--

DROP TABLE IF EXISTS `itemtable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `itemtable` (
  `no` bigint NOT NULL AUTO_INCREMENT,
  `PID` bigint NOT NULL DEFAULT '-1',
  `Name` varchar(45) NOT NULL,
  `Type` int NOT NULL DEFAULT '-1',
  `InvenOrder` int NOT NULL DEFAULT '0',
  `Count` int NOT NULL DEFAULT '1',
  `IconResData` int DEFAULT '-1',
  PRIMARY KEY (`no`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `itemtable`
--

LOCK TABLES `itemtable` WRITE;
/*!40000 ALTER TABLE `itemtable` DISABLE KEYS */;
INSERT INTO `itemtable` VALUES (1,2,'철검',0,0,1,0),(2,2,'포션',2,7,5,2),(3,2,'갑옷',1,1,1,1),(4,2,'포션',2,2,3,2),(5,2,'포션',2,3,3,2),(6,2,'포션',2,4,3,2),(7,2,'갑옷',1,5,1,1),(8,2,'갑옷',1,6,1,1),(9,2,'갑옷',1,8,1,1),(10,1,'포션',2,0,3,2),(11,1,'갑옷',1,1,1,1),(12,1,'갑옷',1,2,1,1),(13,1,'갑옷',1,3,1,1),(14,1,'포션',2,4,1,2),(15,2,'포션',2,9,3,2),(16,2,'포션',2,10,1,2);
/*!40000 ALTER TABLE `itemtable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `partytable`
--

DROP TABLE IF EXISTS `partytable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `partytable` (
  `no` int NOT NULL AUTO_INCREMENT,
  `ID1` bigint DEFAULT NULL,
  `Name1` varchar(45) DEFAULT NULL,
  `Connect1` bigint DEFAULT NULL,
  `ID2` bigint DEFAULT NULL,
  `Name2` varchar(45) DEFAULT NULL,
  `Connect2` bigint DEFAULT NULL,
  `ID3` bigint DEFAULT NULL,
  `Name3` varchar(45) DEFAULT NULL,
  `Connect3` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `partytable`
--

LOCK TABLES `partytable` WRITE;
/*!40000 ALTER TABLE `partytable` DISABLE KEYS */;
/*!40000 ALTER TABLE `partytable` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-08-12  8:53:41

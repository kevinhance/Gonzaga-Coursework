// Kevin Hance
// DBMS HW9

import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.*;
import java.util.Properties;
import java.io.*;
import java.util.*;

public class MySQLTest1 {

    public static void main(String[] args) {
        boolean sentinel = true;
        while(sentinel){
            System.out.print("1. List countries\n2. Add country\n3. Find countries based on gdp and inflation\n4. Update countrys gdp and inflation\n5. Exit\nEnter your choice (1-5):");
            Scanner scanner = new Scanner(System.in);
            String selection = scanner.next();
            switch (selection){
                
                case "1":
                    listCountries();
                    break;
                case "2":
                    addCountry();
                    break;
                case "3":
                    listCountriesByGdpAndInflation();
                    break;
                case "4":
                    updateGDPandInflation();
                    break;
                case "5":
                    sentinel = false;
                    break;
            }
        }
    }

    public static void listCountries(){
        try {
            // connection info
            Properties prop = new Properties();
            FileInputStream in = new FileInputStream("config.properties");
            prop.load(in);
            in.close();

            // connect to datbase
            String hst = prop.getProperty("host");
            String usr = prop.getProperty("user");
            String pwd = prop.getProperty("password");
            String dab = "khance_DB";
            String url = "jdbc:mysql://" + hst + "/" + dab;
            Connection con = DriverManager.getConnection(url, usr, pwd);

            // create and execute query
            Statement stmt = con.createStatement();
            String q = "SELECT country_name, country_code FROM country;";
            ResultSet rs = stmt.executeQuery(q);

            // print results
            System.out.println();
            while(rs.next()) {
                String cname = rs.getString("country_name");
                String ccode = rs.getString("country_code");
                System.out.println(ccode + ", " + cname);
            }
            System.out.println();

            // release resources
            rs.close();
            stmt.close();
            con.close();
        } catch(Exception err) {
            // do something useful
            err.printStackTrace();
        }
    }

    public static void addCountry(){
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Country code................: ");
        String code = scanner.next();
        System.out.print("Country name................: ");
        String name = scanner.next();
        System.out.print("Country per capita gdp (USD): ");
        int gdp = scanner.nextInt();
        System.out.print("Country inflation (pct).....: ");
        float inflation = scanner.nextFloat();

        try {
            // connection info
            Properties prop = new Properties();
            FileInputStream in = new FileInputStream("config.properties");
            prop.load(in);
            in.close();

            // connect to datbase
            String hst = prop.getProperty("host");
            String usr = prop.getProperty("user");
            String pwd = prop.getProperty("password");
            String dab = "khance_DB";
            String url = "jdbc:mysql://" + hst + "/" + dab;
            Connection con = DriverManager.getConnection(url, usr, pwd);

            // create and execute query
            
            String q = "INSERT INTO country(country_code, country_name, gdp, inflation) VALUES (?, ?, ?, ?);";
            PreparedStatement stmt = con.prepareStatement(q);
            stmt.setString(1, code);
            stmt.setString(2, name);
            stmt.setInt(3, gdp);
            stmt.setFloat(4, inflation);
            stmt.execute();

            // print successful
            System.out.println("\nSuccessful\n");

            // release resources
            stmt.close();
            con.close();
        } catch(Exception err) {
            // do something useful
            err.printStackTrace();
        }

    }

    public static void listCountriesByGdpAndInflation(){
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Number of countries to display: ");
        int numCountries = scanner.nextInt();
        System.out.print("Minimum per capita gdp (USD)..: ");
        int minGdp = scanner.nextInt();
        System.out.print("Maximum inflation (pct).......: ");
        float maxInflation = scanner.nextFloat();
        try {
            // connection info
            Properties prop = new Properties();
            FileInputStream in = new FileInputStream("config.properties");
            prop.load(in);
            in.close();

            // connect to datbase
            String hst = prop.getProperty("host");
            String usr = prop.getProperty("user");
            String pwd = prop.getProperty("password");
            String dab = "khance_DB";
            String url = "jdbc:mysql://" + hst + "/" + dab;
            Connection con = DriverManager.getConnection(url, usr, pwd);

            // create and execute query
            
            String q = "SELECT country_name, country_code FROM country WHERE gdp >= ? AND inflation <= ? ORDER BY gdp, inflation ASC LIMIT ?";
            PreparedStatement stmt = con.prepareStatement(q);
            stmt.setInt(1, minGdp);
            stmt.setFloat(2, maxInflation);
            stmt.setInt(3, numCountries);
            ResultSet rs = stmt.executeQuery();

            // print results
            System.out.println();
            while(rs.next()) {
                String cname = rs.getString("country_name");
                String ccode = rs.getString("country_code");
                System.out.println(ccode + ", " + cname);
            }
            System.out.println();

            // release resources
            stmt.close();
            con.close();
        } catch(Exception err) {
            // do something useful
            err.printStackTrace();
        }

    }

    public static void updateGDPandInflation(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Country code................: ");
        String code = scanner.next();
        System.out.print("Country per capita gdp (USD): ");
        int gdp = scanner.nextInt();
        System.out.print("Country inflation (pct).....: ");
        float inflation = scanner.nextFloat();
        try {
            // connection info
            Properties prop = new Properties();
            FileInputStream in = new FileInputStream("config.properties");
            prop.load(in);
            in.close();

            // connect to datbase
            String hst = prop.getProperty("host");
            String usr = prop.getProperty("user");
            String pwd = prop.getProperty("password");
            String dab = "khance_DB";
            String url = "jdbc:mysql://" + hst + "/" + dab;
            Connection con = DriverManager.getConnection(url, usr, pwd);

            // create and execute query
            
            String q = "UPDATE country SET gdp = ?, inflation = ? WHERE country_code = ?";
            PreparedStatement stmt = con.prepareStatement(q);
            stmt.setInt(1, gdp);
            stmt.setFloat(2, inflation);
            stmt.setString(3, code);
            stmt.execute();

            // print successful
            System.out.println("\nSuccessful\n");

            // release resources
            stmt.close();
            con.close();
        } catch(Exception err) {
            // do something useful
            err.printStackTrace();
        }

    }
}
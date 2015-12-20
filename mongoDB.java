import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.MongoClient;
import com.mongodb.QueryBuilder;

///////***********Sample program to output the population and city name with population>70000*******////////
public class pp {		//THe name of the .java file and the class name should match

	
	public static void main(String[] args) {
		MongoClient mongo = new MongoClient( "localhost" , 27017 );	//connect a new MongoClient and connect it to default mongo server
		DB db = mongo.getDB("MongoHW");		//create a DB instance of the MongoHW database in the variable db
		DBCollection table = db.getCollection("zips");	//get the instance of the collection zips in the variable table
		
		ArrayList<String> dbs = new ArrayList<String>();			//display all collections(tables) in the database
				dbs = (ArrayList<String>) mongo.getDatabaseNames();
		for(String db1 : dbs){
			System.out.print(db1 + " ");								
		}
		System.out.println();
		Map<String,Integer> map = new HashMap<>();	//create a HashMap to execute a query on the MongoHW database
		
		
		
//		map.put("city",1);							//insert the names of all the attributes you want to extract
    	map.put("pop",1);							// 1 is to include that column in the output
//		map.put("_id",1);							// 0 is to exclude that column
//		map.put("state",0);
		map.put("loc",1);
		
//		DBCursor cursor = table.find(new BasicDBObject("pop", new BasicDBObject("$gt", 70000)),new BasicDBObject(map));	//execute the query
		// 1. Get the name of the city, the name of the state, and the zip code where the city population > 80000. 
//		DBCursor cursor = table.find(new BasicDBObject("pop", new BasicDBObject("$gt",80000)), new BasicDBObject(map));
		
		// 2. Find the names of the cities that come under the state of Oregon (OR)
//		DBCursor cursor = table.find(new BasicDBObject("state", new BasicDBObject("$eq", "OR")), new BasicDBObject(map));
		
		// 3. Find the names of the cities whose location coordinates are between -110 and 30 
		// (Note: you can put multiple queries in the BasicDBObject)
//	    BasicDBObject result = new BasicDBObject();
//	    ArrayList<BasicDBObject> arr = new ArrayList<BasicDBObject>();
//	    arr.add(new BasicDBObject("loc.0", new BasicDBObject("$gt", -110)));
//	    arr.add(new BasicDBObject("loc.1", new BasicDBObject("$lt", 30)));
//	    result.put("$and", arr);
//	    DBCursor cursor = table.find(result, new BasicDBObject(map));
		
		// 4. Find the names of the cities in the state of Arkansas(AK) where population is greater than 1000
//		BasicDBObject result = new BasicDBObject();
//		ArrayList<BasicDBObject> arr = new ArrayList<BasicDBObject>();
//		arr.add(new BasicDBObject("state", "AK"));
//		arr.add(new BasicDBObject("pop", new BasicDBObject("$gt", 1000)));
//		result.put("$and", arr);
//		DBCursor cursor = table.find(result, new BasicDBObject(map));
	    
		// 5. Find the population and location coordinates of the city "TROY" in the state of "NY".
		BasicDBObject result = new BasicDBObject();
		ArrayList<BasicDBObject> arr = new ArrayList<BasicDBObject>();
		arr.add(new BasicDBObject("state", "NY"));
		arr.add(new BasicDBObject("city", "TROY"));
		result.put("$and", arr);
		DBCursor cursor = table.find(result, new BasicDBObject(map));
	    
		
		while (cursor.hasNext()) {
			System.out.println(cursor.next());		//display the result of the query
		}
		System.out.println("Size of the output: " + cursor.size());		//size of output(no. of rows returned)
	}

}

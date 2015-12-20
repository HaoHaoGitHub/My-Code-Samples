import java.awt.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;

///////***********Sample program to output the population and city name with population>70000*******////////
public class connectMongo {		//THe name of the .java file and the class name should match

	
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
		
		
		
		
		
		
		map.put("city",1);							//insert the names of all the attributes you want to extract
		//map.put("pop", 1);							// 1 is to include that column in the output
		//map.put("_id",1);							// 0 is to exclude that column
		map.put("state",1);
		map.put("loc",1);
//	    //problem #1
		//DBCursor cursor = table.find(new BasicDBObject("pop", new BasicDBObject("$gt", 80000)    ),new BasicDBObject(map));	//execute the query
		
		//problem #2
		//DBCursor cursor = table.find(new BasicDBObject("state", new BasicDBObject("$eq", "OR")    ),new BasicDBObject(map));	//execute the query
		
		//program #3
		/* BasicDBObject result = new BasicDBObject();
		ArrayList<BasicDBObject> obj = new ArrayList<BasicDBObject>();
		obj.add(new BasicDBObject("loc.0", new BasicDBObject("$gt", -110)));
		obj.add(new BasicDBObject("loc.1", new BasicDBObject("$lt", 30)));
		result.put("$and", obj); 
		//System.out.println(cursor.toString());
		DBCursor cursor = table.find(result,new BasicDBObject(map));
		
		while (((Iterator<DBObject>) cursor).hasNext()) {
			System.out.println(((Iterator<DBObject>) cursor).next());		//display the result of the query
		}
		System.out.println("Size of the output: " + cursor.size());		//size of output(no. of rows returned)
		*/
		
		//program #4
		
		/* BasicDBObject result = new BasicDBObject();
		ArrayList<BasicDBObject> obj = new ArrayList<BasicDBObject>();
		obj.add(new BasicDBObject("state", "AK"));
		obj.add(new BasicDBObject("pop", new BasicDBObject("$gt", 1000)));
		result.put("$and", obj);
		DBCursor cursor = table.find(result,new BasicDBObject(map));
		while (((Iterator<DBObject>) cursor).hasNext()) {
			System.out.println(((Iterator<DBObject>) cursor).next());		//display the result of the query
		}
		System.out.println("Size of the output: " + cursor.size());  */
		
		
		
		//problem #5
		BasicDBObject result = new BasicDBObject();
		ArrayList<BasicDBObject> obj = new ArrayList<BasicDBObject>();
		obj.add(new BasicDBObject("state", "NY"));
		obj.add(new BasicDBObject("city", "TROY"));	
		result.put("$and", obj);
		//	System.out.println(cursor.toString());
		DBCursor cursor = table.find(result,new BasicDBObject(map));	
		
		while (((Iterator<DBObject>) cursor).hasNext()) {
			System.out.println(((Iterator<DBObject>) cursor).next());		//display the result of the query
		}
		System.out.println("Size of the output: " + cursor.size());		//size of output(no. of rows returned)
	}

}

// Import the MongoDB client
const { MongoClient } = require("mongodb");

// Connection URL
const url = "mongodb://localhost:27017";
const client = new MongoClient(url);

// Database and Collection Names
const dbName = "healthcareDB";
const collectionName = "patients";

async function run() {
  try {
    await client.connect();
    console.log("Connected successfully to MongoDB server");

    const db = client.db(dbName);
    const collection = db.collection(collectionName);

    // Data to insert
    const patients = [
      {
        Name: "G.Sai Abiram",
        PhoneNo: "7416061028",
        EMNo: "xxxxxx123",
        Age: 19,
        BloodGroup: "O+ve",
        UniqueID: "OMZAYo",
      },
      {
        Name: "N.Nikith",
        PhoneNo: "9299208982",
        EMNo: "xxxxxxxx456",
        Age: 18,
        BloodGroup: "B-ve",
        UniqueID: "XYZ123",
      },
      {
        Name: "Sahithi",
        PhoneNo: "8341571170",
        EMNo: "xxxxxxx789",
        Age: 18,
        BloodGroup: "B+ve",
        UniqueID: "ABC123",
      },
    ];

    // Insert data into collection
    const insertResult = await collection.insertMany(patients);
    console.log("Inserted documents =>", insertResult.insertedCount);

  } finally {
    await client.close();
  }
}

run().catch(console.dir);
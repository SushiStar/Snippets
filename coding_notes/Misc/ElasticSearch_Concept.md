# Elastic Search Concepts

#### Fields
Fields are the smallest individual unit of data in Elasticsearch. Each field has a defined datatype and contains a single piece of data.

#### Multi-fields
These fields can be indexed in more than one way to produce more search results. This option is available easily through the "multi-fields" option, which as you might have guessed allow for fields to be indexed in multiple ways.

#### Documents
Documents are JSON objects that are stored within an Elasticsearch index and considered the base unit of storage. In the world of relational databases, documents can be compared to a row in a table.
Data in documents is defined with fields comprised of keys and values. A key is the name of the field, and a value can be an item of many different types, such as a string, a number, a boolean expression, or an array of values.

Documents also contain reserved fields that constitute the document metadata such as:
+ `_index` -- the index where the document resides
+ `_type` -- the type that the document represents
+ `_id` -- the unique identifier for the document

An example of the document:
```JSON
{
  "_id": 3,
  "_type": ["your index type"],
  "_index": ["your index name"],
  "_source": {
    "age": 28,
    "name": ["daniel"],
    "year": 1989,
  }
}
```

#### Index
Indices, the largest unit of data in Elasticsearch, are logical partitions of documents and can be compared to a database in the world of relational database.
You can have as many indices defined in Elasticsearch as you want. These in turn will hold documents that are unique to each index. Indices are identified by lowercase names that refer to actions that are *performed actions* on the documents that are inside each index.  

#### Shards
Shards are single Lucene index. They are the building blocks of Elasticsearch and what facilitate its scalability.
Index size is a common cause of Elasticsearch crashes. Since there is no limit to how many documents you can store on each index, an index may take up an amount of disk space that exceeds the limits of the hosting server.
When you create an index, you can define how many shards you want. Each shard is an independent Lucene index that can be hosted anywhere in your cluster.

#### Replicas
Replicas, as the name impiles, are Elasticsearch fail-safe mechanisms and are basically copies of your index's shards. This is a useful backup system for a rainy day -- or, in other words, when a node crashe. Replicas also serve read requests, so adding replicas can help to increase search performance. 

#### Analyzers
Analyzers are used during indexing to break down -- or parse -- phrases and expressions into their constiuent terms. Defined within an index, an analyzer consists of a single tokenizer and any number of token filters. 

#### Instances and Nodes
In a cluster, different responsibilities are assigned to the various node types:
+ Data nodes -- stores data and executes data-related operations such as search and aggregation.
+ Master nodes -- in charge of cluster-wide management and configuration actions such as adding and removing nodes.
+ Client nodes -- forwards cluster requests to the master node and data-related requests to data nodes.
+ Tribe nodes -- act as a client node, performing read and write operations against all of the nodes in the cluster.
+ Ingestion nodes -- for pre-processing documents before indexing.
+ Machine Learning nodes -- these are nodes available under Elastic's Basic License that enable machine learning tasks. Machine learning nodes have xpack.ml.enabled and node.ml set to true.

#### Cluster
An Elasticsearch cluster is comprised of one or more Elasticsearch nodes. As with *nodes*, each cluster has a unique identifier that must be used by any node attempting to join the cluster.

#### TBD DB

tl;dr: A DBMS optimized for ultra-fast reads.
pros: Stores data on both a columnar basis and a row basis, allowing the query planner to choose which layout format to read from for best performance, potentially even mid-query.
cons: doubles the database's size on disk and write speed

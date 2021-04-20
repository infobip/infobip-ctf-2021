package org.ctf;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.persistence.EntityManager;
import javax.persistence.NoResultException;
import javax.persistence.PersistenceContext;
import java.util.Arrays;
import java.util.List;

@RestController
@RequestMapping("/cars")
public class CarController {

    @PersistenceContext
    private EntityManager entityManager;

    @GetMapping
    public ResponseEntity getAll() {
        ResponseEntity response;
        try {
            List cars = entityManager.createNativeQuery("SELECT * FROM CARS", CarModel.class).getResultList();
            response = new ResponseEntity<>(cars, HttpStatus.OK);
        } catch(NoResultException e) {
            response = new ResponseEntity<>(HttpStatus.NOT_FOUND);
        } catch(Exception e) {
            response = new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
        }
        return response;
    }

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
}

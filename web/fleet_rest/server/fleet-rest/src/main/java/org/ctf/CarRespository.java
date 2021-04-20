package org.ctf;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CarRespository extends CrudRepository<CarModel, Long> {
}

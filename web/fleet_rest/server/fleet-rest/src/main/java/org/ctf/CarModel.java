package org.ctf;

import com.fasterxml.jackson.annotation.JsonIgnore;

import javax.persistence.*;

@Entity
@Table(name = "cars")
public class CarModel {

    @Id
    @Column(name = "car_id")
    private Long carId;
    @Column(name = "manufacturer")
    private String manufacturer;
    @Column(name = "model")
    private String model;
    @Column(name = "year")
    private String year;
    @Column(name = "hp")
    private String hp;
    @JsonIgnore
    @Column(name = "secret")
    private String secret;

    public CarModel() {
    }

    public CarModel(Long carId, String manufacturer, String model, String year, String hp, String secret) {
        this.carId = carId;
        this.manufacturer = manufacturer;
        this.model = model;
        this.year = year;
        this.hp = hp;
        this.secret = secret;
    }

    public Long getCarId() {
        return carId;
    }

    public void setCarId(Long carId) {
        this.carId = carId;
    }

    public String getManufacturer() {
        return manufacturer;
    }

    public void setManufacturer(String manufacturer) {
        this.manufacturer = manufacturer;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getYear() {
        return year;
    }

    public void setYear(String year) {
        this.year = year;
    }

    public String getHp() {
        return hp;
    }

    public void setHp(String hp) {
        this.hp = hp;
    }

    public String getSecret() {
        return secret;
    }

    public void setSecret(String secret) {
        this.secret = secret;
    }
}

//
//  main.cpp
//  Weather Data
//
//  Created by Mo Li on 1/3/21.
//

#include <iostream>
#include <vector>

struct Obeserver {
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

struct DisplayElement {
public:
    virtual void display() = 0;
};

struct Subject {
public:
    virtual void registerObserver(Obeserver* o) = 0;
    virtual void removeObserver(Obeserver* o) = 0;
    virtual void notifyObservers() = 0;
};

class CurrentConditionDisplay : public Obeserver, DisplayElement {
    float temperature;
    float humidity;
    Subject* weatherData;
public:
    CurrentConditionDisplay(Subject* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    void update(float temp, float humidity, float pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        display();
    }
    void display() {
        std::cout << "Current Conditions: " << temperature << " Degrees and " << humidity << " % humidity" << std::endl;
    }
};

class CurrentConditionDisplay2 : public Obeserver, DisplayElement {
    float temperature;
    float humidity;
    float pressure;
    Subject* weatherData;
public:
    CurrentConditionDisplay2(Subject* weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    void update(float temp, float humidity, float pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        display();
    }
    void display() {
        std::cout << "Current Conditions2: " << temperature << " Degrees and " << humidity << " % humidity and pressure is " << pressure << std::endl;
    }
};

class WeatherData : public Subject {
    std::vector<Obeserver*> observers;
    float temperature;
    float humidity;
    float pressure;
    
public:
    void registerObserver(Obeserver* o) {
        observers.emplace_back(o);
    }
    void removeObserver(Obeserver* o) {
        auto it = observers.begin();
        while (it != observers.end()) {
            if (*it == o) {
                observers.erase(it);
                break;
            }
            it++;
        }
    }
    void notifyObservers() {
        auto it = observers.begin();
        while (it != observers.end()) {
            Obeserver* observer = *it;
            observer->update(temperature, humidity, pressure);
            it++;
        }
    }

    void measurementsChanged() {
        notifyObservers();
    }
    
    void setMeasurements(float temp, float humidity, float pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    WeatherData* weatherData = new WeatherData();
    CurrentConditionDisplay* currentDisplay = new CurrentConditionDisplay(weatherData);
    CurrentConditionDisplay2* currentDisplay2 = new CurrentConditionDisplay2(weatherData);
    weatherData->setMeasurements(80, 65, 30.4);
    weatherData->removeObserver(currentDisplay);
    weatherData->setMeasurements(82, 70, 29.2);
    weatherData->removeObserver(currentDisplay2);
    weatherData->setMeasurements(78, 90, 29.4);
    return 0;
}

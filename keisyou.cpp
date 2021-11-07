#include <iostream>
#include <memory>

class Movile{
    public:
    virtual float getV()=0;
};

class Car:public Movile{
    private:
    float v;

    public:
    Car(const float v):v(v){};
    float getV() override{
        return v;
    }
};


class Bike:public Movile{
    private:
    float v;
    float u;

    public:
    Bike(const float v,const float u):v(v),u(u){};
    float getV() override{
        return v * u;
    }
};

class Human:public Movile{
    private:
    float v;
    float u;
    float w;

    public:
    Human(const float u,const float v,const float w):u(u),v(v),w(w){};

    float getV() override{
        return u * v * w;
    }
};

int main(){
    std::shared_ptr<Movile> movile;
    auto car = std::make_shared<Car>(1.0);
    auto bike = std::make_shared<Bike>(2.0,3.0);
    auto human = std::make_shared<Human>(3.0,2.0,3.0);

    movile = car;
    std::cout << movile->getV() << std::endl;

    movile = bike;
    std::cout << movile->getV() << std::endl;

    movile = human;
    std::cout << movile->getV() << std::endl;


    return 0;
}
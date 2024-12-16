#include <iostream>
#include "canvas.cpp"
#include "gravity.cpp"


Body* getBodyFromUser() {
    double mass, x, y, vx, vy;
    std::cout << "Cismin kutlesini (mass), baslangic konumunu (x, y) ve hizini (vx, vy) girin:\n";
    std::cout << "Ornek Giris (Lutfen Ornege uygun sekilde girin): 100 0 0 0.1 0.2\n";
    while (true) {
        
        std::cin >> mass >> x >> y >> vx >> vy;

        if (!std::cin.fail()) {
          break;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Lutfen gecerli bir sayi girin.\n";
    }
    return new Body(mass, Vector(x, y), Vector(vx, vy));
}

Rocket* getRocketFromUser() {
    double mass, x, y, vx, vy, exhaustVel, exhaustRate;
    std::cout << "Roketin kutlesini (mass), baslangic konumunu (x, y), hizini (vx, vy), itki hiz, (exhaustVel) ve yakit tuketim oranini (exhaustRate) girin:\n";
    std::cout << "Ornek Giris (Lutfen Ornege uygun sekilde girin): 50 0 0 0 0 1 0.0001\n";
    while (true) {

        std::cin >> mass >> x >> y >> vx >> vy >> exhaustVel >> exhaustRate;

        if (!std::cin.fail()) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Lutfen gecerli bir sayi girin.\n";
    }

    return new Rocket(mass, Vector(x, y), Vector(vx, vy), Vector(exhaustVel, 0), exhaustRate);
}

Gezegen* getGezegenFromUser() {
    double mass, x, y, vx, vy, orbitalSpeed;
    std::cout << "Gezegenin kutlesini (mass), baslangic konumunu (x, y), hizini (vx, vy), Yorunge Hizini (orbitalSpeed) girin:\n";
    std::cout << "Ornek Giris (Lutfen Ornege uygun sekilde girin): 3000 0 0 0 0 99\n";
    while (true) {

        std::cin >> mass >> x >> y >> vx >> vy >> orbitalSpeed;

        if (!std::cin.fail()) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Lutfen gecerli bir sayi girin.\n";
    }
   
    return new Gezegen(mass, Vector(x, y), Vector(vx, vy), orbitalSpeed);
}

Asteroid* getAsteroidFromUser() {
    double mass, x, y, vx, vy;
    std::cout << "Asteroidin kutlesini (mass), baslangic konumunu (x, y), hizini (vx, vy) girin:\n";
    std::cout << "Ornek Giris (Lutfen Ornege uygun sekilde girin): 50 0 0 0 0\n";
    while (true) {

        std::cin >> mass >> x >> y >> vx >> vy;
        if (!std::cin.fail()) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Lutfen gecerli bir sayi girin.\n";
    }

    return new Asteroid(mass, Vector(x, y), Vector(vx, vy));
}

int main() {
    constexpr double TIME_STEP = 1.0;

    std::string filename;
    Universe universe(TIME_STEP);
    std::vector<Body*> tempBodies;

    int bodyCount, rocketCount, planetCount, asteroidCount;
    std::cout << "Lutfen Simulasyonu adlandirin\n>>> ";
    std::cin >> filename;

    canvas graphic(filename);
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "\t\t\t   SIMULASYON BASLATILIYOR\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Kac tane cisim eklemek istiyorsunuz?\n>>> ";
    std::cin >> bodyCount;
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Sisteme " << bodyCount << " adet cisim eklenecek.\n";
    std::cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < bodyCount; ++i) {
        std::cout << "Cisim " << i + 1 << " bilgilerini giriniz:\n";
        Body* body = getBodyFromUser();
        tempBodies.push_back(body);
        universe.addBody(body);
        std::cout << "-----------------------------------------------------------\n";
    }

    std::cout << "Kac tane roket eklemek istiyorsunuz?\n>>> ";
    std::cin >> rocketCount;
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Sisteme " << rocketCount << " adet roket eklenecek.\n";
    std::cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < rocketCount; ++i) {
        std::cout << "Roket " << i + 1 << " bilgilerini giriniz:\n";
        Rocket* rocket = getRocketFromUser();
        tempBodies.push_back(rocket);
        universe.addBody(rocket);
        std::cout << "-----------------------------------------------------------\n";
    }

    std::cout << "Kac tane Gezegen eklemek istiyorsunuz?\n>>> ";
    std::cin >> planetCount;
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Sisteme " << planetCount << " adet Gezegen eklenecek.\n";
    std::cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < planetCount; ++i) {
        std::cout << "Gezegen " << i + 1 << " bilgilerini giriniz:\n";
        Gezegen* gezegen = getGezegenFromUser();
        tempBodies.push_back(gezegen);
        universe.addBody(gezegen);
        std::cout << "-----------------------------------------------------------\n";
    }

    std::cout << "Kac tane Asteroid eklemek istiyorsunuz?\n>>> ";
    std::cin >> asteroidCount;
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Sisteme " << asteroidCount << " adet Asteroid eklenecek.\n";
    std::cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < asteroidCount; ++i) {
        std::cout << "Asteroid " << i + 1 << " bilgilerini giriniz:\n";
        Asteroid* asteroid = getAsteroidFromUser();
        tempBodies.push_back(asteroid);
        universe.addBody(asteroid);
        std::cout << "-----------------------------------------------------------\n";
    }

    std::cout << "\nSimulasyon calistiriliyor... Lutfen bekleyiniz...\n";
    std::cout << "-----------------------------------------------------------\n";

    std::vector<std::string> colors = { "red", "green", "blue", "magenta", "orange", "cyan", "yellow" };

    graphic.startDoc();
    graphic.drawFrame();

    for (size_t i = 0; i < universe.bodies.size(); ++i) {
        std::string color = colors[i % colors.size()];
        graphic.drawPoint(universe.bodies[i]->position.x, universe.bodies[i]->position.y, color, 3);
    }

    for (int t = 0; t < 5000; ++t) {
        universe.step();

        for (size_t i = 0; i < universe.bodies.size(); ++i) {
            std::string color = colors[i % colors.size()];
            graphic.drawPoint(universe.bodies[i]->position.x, universe.bodies[i]->position.y, color);
        }
    }

    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Simulasyon tamamlandi. Grafik dosyasi hazirlaniyor...\n";
    std::cout << "Grafik cikti dosyasi: " << filename << "\n";
    std::cout << "-----------------------------------------------------------\n";
    graphic.finishDoc();

    for (Body* body : tempBodies) {
        delete body;
    }

    return 0;
}
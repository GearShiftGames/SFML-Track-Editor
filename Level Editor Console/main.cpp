#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace sf;

void save();
void load();

// Variables
std::vector<Sprite*> barriers;
std::vector<Sprite*> checkpoints;
std::vector<Sprite*> vehicles;
std::vector< std::vector<int> > ids;
std::string type = "";
int selected = -1;
int enteringId = 3;

int main() {

	RenderWindow window(VideoMode(1920, 1080), ""); // , Style::Fullscreen);

	Sprite spriteBackground;
	Texture barrierTexture, checkpointTexture, vehicleTexture, background;
	Font font;
	Text debugText, idText("ID = ", font), nextText("nextID = ", font), pathText("pathID = ", font);

	idText.setPosition(debugText.getPosition().x,	debugText.getPosition().y + 40);
	nextText.setPosition(idText.getPosition().x,	idText.getPosition().y + 40);
	pathText.setPosition(nextText.getPosition().x,	nextText.getPosition().y + 40);
	
	if (!background.loadFromFile("graphics/background.png")) {
		std::cout << "Background failed to load. Please restart with \"background.png\" in the graphics folder." << std::endl;
	} else {
		spriteBackground.setTexture(background);
	}
	if (!barrierTexture.loadFromFile("graphics/barrier.png")) {
		std::cout << "Barrier failed to load. Please restart with \"barrier.png\" in the graphics folder." << std::endl;
	}
	if (!checkpointTexture.loadFromFile("graphics/checkpoint.png")) {
		std::cout << "Checkpoint failed to load. Please restart with \"checkpoint.png\" in the graphics folder." << std::endl;
	}
	if (!vehicleTexture.loadFromFile("graphics/vehicle.png")) {
		std::cout << "Vehicle failed to load. Please restart with \"vehicle.png\" in the graphics folder." << std::endl;
	}
	if (!font.loadFromFile("graphics/tahoma.ttf")) {
		std::cout << "Font failed to load. Please restart with \"tahoma.ttf\" in the graphics folder." << std::endl;
	} else {
		debugText.setFont(font);
		debugText.setCharacterSize(30);
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {

				// GENERAL EVENTS
			case Event::Closed:
				window.close();
				break;

				// KEYBOARD EVENTS
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
				else if (event.key.code == Keyboard::B) {
					std::cout << "\"B\" pressed. Adding a barrier at (0, 0)." << std::endl;
					Sprite* barrier = new Sprite(barrierTexture);
					barrier->setOrigin(Vector2f(barrier->getTexture()->getSize().x / 2, barrier->getTexture()->getSize().y / 2));
					barriers.push_back(barrier);
					selected = barriers.size() - 1;
					type = "barrier";
				}
				else if (event.key.code == Keyboard::C) {
					std::cout << "\"C\" pressed. Adding a checkpoint at (0, 0)." << std::endl;
					Sprite* checkpoint = new Sprite(checkpointTexture);
					checkpoint->setOrigin(Vector2f(checkpoint->getTexture()->getSize().x / 2, checkpoint->getTexture()->getSize().y / 2));
					checkpoints.push_back(checkpoint);
					std::vector<int> intVector = std::vector<int>(3);
					ids.push_back(intVector);
					selected = checkpoints.size() - 1;
					type = "checkpoint";
				}
				else if (event.key.code == Keyboard::V) {
					std::cout << "\"V\" pressed. Adding a vehicle at (0, 0)." << std::endl;
					Sprite* vehicle = new Sprite(vehicleTexture);
					vehicle->setOrigin(Vector2f(vehicle->getTexture()->getSize().x / 2, vehicle->getTexture()->getSize().y / 2));
					vehicles.push_back(vehicle);
					selected = vehicles.size() - 1;
					type = "vehicle";
				}
				else if (event.key.code == Keyboard::R) {
					std::cout << "\"R\" pressed. Where did that sprite go?" << std::endl;
					if (type == "barrier") {
						barriers.erase(barriers.begin() + selected);
					}
					else if (type == "checkpoint") {
						checkpoints.erase(checkpoints.begin() + selected);
					}
					else if (type == "vehicle") {
						vehicles.erase(vehicles.begin() + selected);
					}
				}
				else if (event.key.code == Keyboard::F) {
					std::cout << "\"F\" pressed. Attempting to save." << std::endl;
					save();
				}
				else if (event.key.code == Keyboard::L) {
					std::cout << "\"L\" pressed. Attempting to load." << std::endl;
					load();
					for (Sprite* s : barriers) {
						s->setTexture(barrierTexture);
						s->setOrigin(Vector2f(s->getTexture()->getSize().x / 2, s->getTexture()->getSize().y / 2));
					}
					for (Sprite* s : checkpoints) {
						s->setTexture(checkpointTexture);
						s->setOrigin(Vector2f(s->getTexture()->getSize().x / 2, s->getTexture()->getSize().y / 2));
					}
					for (Sprite* s : vehicles) {
						s->setTexture(vehicleTexture);
						s->setOrigin(Vector2f(s->getTexture()->getSize().x / 2, s->getTexture()->getSize().y / 2));
					}
				}
				else if (event.key.code == Keyboard::T) {
					if (type == "checkpoint") {
						enteringId = 0;
						ids[selected][0] = 0;
						ids[selected][1] = 0;
						ids[selected][2] = 0;
					}
				}
				else if (event.key.code == Keyboard::Return) {
					if (type == "checkpoint") {
						enteringId++;
					}
				}
				else if (event.key.code == Keyboard::W) {
					std::cout << "\"W\" pressed. Moving sprite northwards." << std::endl;
					if (type == "barrier") {
						barriers[selected]->move(0.0f, -1.0f);
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->move(0.0f, -1.0f);
					}
					else if (type == "vehicle") {
						vehicles[selected]->move(0.0f, -1.0f);
					}
				}
				else if (event.key.code == Keyboard::A) {
					std::cout << "\"A\" pressed. Moving sprite to the left, to the left." << std::endl;
					if (type == "barrier") {
						barriers[selected]->move(-1.0f, 0.0f);
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->move(-1.0f, 0.0f);
					}
					else if (type == "vehicle") {
						vehicles[selected]->move(-1.0f, 0.0f);
					}
				}
				else if (event.key.code == Keyboard::S) {
					std::cout << "\"S\" pressed. Moving sprite southwards." << std::endl;
					if (type == "barrier") {
						barriers[selected]->move(0.0f, 1.0f);
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->move(0.0f, 1.0f);
					}
					else if (type == "vehicle") {
						vehicles[selected]->move(0.0f, 1.0f);
					}
				}
				else if (event.key.code == Keyboard::D) {
					std::cout << "\"D\" pressed. Moving sprite to the right." << std::endl;
					if (type == "barrier") {
						barriers[selected]->move(1.0f, 0.0f);
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->move(1.0f, 0.0f);
					}
					else if (type == "vehicle") {
						vehicles[selected]->move(1.0f, 0.0f);
					}
				}
				else if (event.key.code == Keyboard::Q) {
					std::cout << "\"Q\" pressed. Rotating sprite anti-clockwise." << std::endl;
					if (type == "barrier") {
						barriers[selected]->rotate(-1.0f);
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->rotate(-1.0f);
					}
					else if (type == "vehicle") {
						vehicles[selected]->rotate(-1.0f);
					}
				}
				else if (event.key.code == Keyboard::E) {
					std::cout << "\"E\" pressed. Rotating sprite clockwise." << std::endl;
					if (type == "barrier") {
						barriers[selected]->rotate(1.0f);
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->rotate(1.0f);
					}
					else if (type == "vehicle") {
						vehicles[selected]->rotate(1.0f);
					}
				}
				else if (event.key.code == Keyboard::Num0 || event.key.code == Keyboard::Numpad0) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 0;
					}
				}
				else if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Numpad1) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 1;
					}
				}
				else if (event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Numpad2) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 2;
					}
				}
				else if (event.key.code == Keyboard::Num3 || event.key.code == Keyboard::Numpad3) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 3;
					}
				}
				else if (event.key.code == Keyboard::Num4 || event.key.code == Keyboard::Numpad4) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 4;
					}
				}
				else if (event.key.code == Keyboard::Num5 || event.key.code == Keyboard::Numpad5) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 5;
					}
				}
				else if (event.key.code == Keyboard::Num6 || event.key.code == Keyboard::Numpad6) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 6;
					}
				}
				else if (event.key.code == Keyboard::Num7 || event.key.code == Keyboard::Numpad7) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 7;
					}
				}
				else if (event.key.code == Keyboard::Num8 || event.key.code == Keyboard::Numpad8) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 8;
					}
				}
				else if (event.key.code == Keyboard::Num9 || event.key.code == Keyboard::Numpad9) {
					if (enteringId <= 2) {
						ids[selected][enteringId] += 9;
					}
				}
				break;

				// MOUSE EVENTS
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left) {
					std::cout << "Left clicked at: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
					if (type == "barrier") {
						barriers[selected]->setPosition(event.mouseButton.x, event.mouseButton.y);
						std::cout << "Barrier[" << selected << "] moved to: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
					}
					else if (type == "checkpoint") {
						checkpoints[selected]->setPosition(event.mouseButton.x, event.mouseButton.y);
						std::cout << "Checkpoint[" << selected << "] moved to: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
					}
					else if (type == "vehicle") {
						vehicles[selected]->setPosition(event.mouseButton.x, event.mouseButton.y);
						std::cout << "Vehicle[" << selected << "] moved to: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
					}
				}
				else if (event.mouseButton.button == Mouse::Right) {
					std::cout << "Right clicked at: " << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
					for (int i = 0; i < barriers.size(); i++) {
						if (event.mouseButton.x >= (barriers[i]->getPosition().x - barriers[i]->getTexture()->getSize().x / 2) && 
							event.mouseButton.x <= (barriers[i]->getPosition().x + barriers[i]->getTexture()->getSize().x / 2) &&
							event.mouseButton.y >= (barriers[i]->getPosition().y - barriers[i]->getTexture()->getSize().y / 2) &&
							event.mouseButton.y <= (barriers[i]->getPosition().y + barriers[i]->getTexture()->getSize().y / 2)) {
							selected = i;
							type = "barrier";
							std::cout << "Barrier[" << i << "] is now selected." << std::endl;
						}
					}
					for (int i = 0; i < checkpoints.size(); i++) {
						if (event.mouseButton.x >= (checkpoints[i]->getPosition().x - checkpoints[i]->getTexture()->getSize().x / 2) &&
							event.mouseButton.x <= (checkpoints[i]->getPosition().x + checkpoints[i]->getTexture()->getSize().x / 2) &&
							event.mouseButton.y >= (checkpoints[i]->getPosition().y - checkpoints[i]->getTexture()->getSize().y / 2) &&
							event.mouseButton.y <= (checkpoints[i]->getPosition().y + checkpoints[i]->getTexture()->getSize().y / 2)) {
							selected = i;
							type = "checkpoint";
							std::cout << "Checkpoint[" << i << "] is now selected." << std::endl;
						}
					}
					for (int i = 0; i < vehicles.size(); i++) {
						if (event.mouseButton.x >= (vehicles[i]->getPosition().x - vehicles[i]->getTexture()->getSize().x / 2) &&
							event.mouseButton.x <= (vehicles[i]->getPosition().x + vehicles[i]->getTexture()->getSize().x / 2) &&
							event.mouseButton.y >= (vehicles[i]->getPosition().y - vehicles[i]->getTexture()->getSize().y / 2) &&
							event.mouseButton.y <= (vehicles[i]->getPosition().y + vehicles[i]->getTexture()->getSize().y / 2)) {
							selected = i;
							type = "vehicle";
							std::cout << "Vehicle[" << i << "] is now selected." << std::endl;
						}
					}
				}
				break;

			default:
				break;
			}
		}

		if (enteringId <= 2) {
			debugText.setString("Enter ID's for checkpoint[" + std::to_string(selected) + "]: ");
		} else {
			debugText.setString("Selected Object: " + type + "[" + std::to_string(selected) + "]");
		}
		
		window.clear();
		window.draw(spriteBackground);
		for (int i = 0; i < barriers.size(); i++) {
			window.draw(*barriers[i]);
		}
		for (int i = 0; i < checkpoints.size(); i++) {
			window.draw(*checkpoints[i]);
		}
		for (int i = 0; i < vehicles.size(); i++) {
			window.draw(*vehicles[i]);
		}
		window.draw(debugText);
		if (type == "checkpoint") {
			if (enteringId == 0) {
				idText.setString("ID = " + std::to_string(ids[selected][0]));
				window.draw(idText);
			} else if (enteringId == 1) {
				nextText.setString("nextID = " + std::to_string(ids[selected][1]));
				window.draw(nextText);
			} else if (enteringId == 2) {
				pathText.setString("pathID = " + std::to_string(ids[selected][2]));
				window.draw(pathText);
			} else if (enteringId > 2) {
				idText.setString("ID = " + std::to_string(ids[selected][0]));
				window.draw(idText);
				nextText.setString("nextID = " + std::to_string(ids[selected][1]));
				window.draw(nextText);
				pathText.setString("pathID = " + std::to_string(ids[selected][2]));
				window.draw(pathText);
			}
		}
		window.display();
	}

	return 0;
}

void save() {
	std::ofstream file;
	std::cout << "Saving barriers.." << std::endl;
	file.open("track/barriers.ini");
	for (int i = 0; i < barriers.size(); i++) {
		file << "[" << i << "]" << std::endl;
		file << "positionX=" << barriers[i]->getPosition().x << std::endl;
		file << "positionY=" << barriers[i]->getPosition().y << std::endl;
		file << "rotation=" << barriers[i]->getRotation() << std::endl;
		file << std::endl;
	}
	file.close();

	std::cout << "Saving checkpoints.." << std::endl;
	file.open("track/checkpoints.ini");
	for (int i = 0; i < checkpoints.size(); i++) {
		file << "[" << i << "]" << std::endl;
		file << "ID=" << ids[i][0] << std::endl;
		file << "nextID=" << ids[i][1] << std::endl;
		file << "pathID=" << ids[i][2] << std::endl;
		file << "positionX=" << checkpoints[i]->getPosition().x << std::endl;
		file << "positionY=" << checkpoints[i]->getPosition().y << std::endl;
		file << "rotation=" << checkpoints[i]->getRotation() << std::endl;
		file << std::endl;
	}
	file.close();

	std::cout << "Saving vehicles.." << std::endl;
	file.open("track/vehicles.ini");
	for (int i = 0; i < vehicles.size(); i++) {
		file << "[" << i << "]" << std::endl;
		file << "positionX=" << vehicles[i]->getPosition().x << std::endl;
		file << "positionY=" << vehicles[i]->getPosition().y << std::endl;
		file << "rotation=" << vehicles[i]->getRotation() << std::endl;
		file << std::endl;
	}
	file.close();

	std::cout << "File saved." << std::endl;
}

void load() {
	std::string readLine;
	std::string subLine;
	std::ifstream file;

	std::cout << "Loading barriers.." << std::endl;
	file.open("track/barriers.ini");
	while (getline(file, readLine)) {
		if (readLine.substr(0, 1) == "[") {
			Sprite* barrier = new Sprite();
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			barrier->move(Vector2f(std::stoi(subLine), 0));
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			barrier->move(Vector2f(0, std::stoi(subLine)));
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			barrier->rotate(std::stof(subLine));
			barriers.push_back(barrier);
		}
	}
	file.close();

	std::cout << "Loading checkpoints.." << std::endl;
	file.open("track/checkpoints.ini");
	while (getline(file, readLine)) {
		if (readLine.substr(0, 1) == "[") {
			Sprite* checkpoint = new Sprite();
			std::vector<int> id = std::vector<int>(3);
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			id[0] = std::stoi(subLine);
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			id[1] = std::stoi(subLine);
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			id[2] = std::stoi(subLine);
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			checkpoint->move(Vector2f(std::stoi(subLine), 0));
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			checkpoint->move(Vector2f(0, std::stoi(subLine)));
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			checkpoint->rotate(std::stof(subLine));
			checkpoints.push_back(checkpoint);
			ids.push_back(id);
		}
	}
	file.close();

	std::cout << "Loading vehicles.." << std::endl;
	file.open("track/vehicles.ini");
	while (getline(file, readLine)) {
		if (readLine.substr(0, 1) == "[") {
			Sprite* vehicle = new Sprite();
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			vehicle->move(Vector2f(std::stoi(subLine), 0));
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			vehicle->move(Vector2f(0, std::stoi(subLine)));
			getline(file, readLine);
			subLine = readLine.substr(readLine.find("=") + 1);
			vehicle->rotate(std::stof(subLine));
			vehicles.push_back(vehicle);
		}
	}
	file.close();

	std::cout << "Track loaded." << std::endl;
}
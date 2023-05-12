#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
using namespace sf;
bool isCollide(Sprite s1, Sprite s2) {
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());//fonction qui determine l'intersection de deux sprites
}
int main()
{
	srand(time(0));
	bool lose = false;
	bool soundPlayed = false;//variable booléene pour la manipulation de sons
	bool sound2Played = false;
	bool sound3Played = false;
	bool sound4Played = false;
	bool ballLost = false;//varaible pour la détection de la perte du ballon
	bool gameStarted = false;//variable pour la detection du début du jeu(lorsque le joueur presse sur le start button)
	int score = 0;
	int n = 0;
	int i;
	int nbChance = 1;
	float dx = 6, dy = 5;
	RenderWindow window(VideoMode(600, 600), "ARKANOID");
	window.setFramerateLimit(60);
	Texture background, ball, paddle, block;
	background.loadFromFile("../pics/back3.jpg");
	ball.loadFromFile("../pics/ball.png");
	paddle.loadFromFile("../pics/paddle2.png");
	block.loadFromFile("../pics/block02.png");
	Sprite Sbackground(background);
	Sprite Sball(ball);
	Sprite Spaddle(paddle);
	Sbackground.setScale(0.7, 0.7); //pour modifiier la taille
	Sball.setScale(0.1f, 0.1f);//diminuer la taille de l'image
	Spaddle.setScale(0.5f, 0.5f);
	Spaddle.setPosition(300.0f, 580.0f);
	Sball.setPosition(300.0f, 575.0f);
	Sprite blocks[1000];//un tableau de sprite qui va contenir les sprites de blocks
	Font font;
	font.loadFromFile("../font/Arimo-Italic.ttf");
	Text scoreText;//a text to show the score
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(Color::Red);
	scoreText.setPosition(50, 450);
	Texture startButtonTexture;//a start button
	startButtonTexture.loadFromFile("../pics/start-button2.png");
	Sprite startButtonSprite(startButtonTexture);
	startButtonSprite.setPosition(160, 320); // positionner le start_button
	startButtonSprite.setScale(0.5f, 0.5f);
	Texture gameName;
	gameName.loadFromFile("../pics/game-name.png");
	Sprite SgameName(gameName);
	SgameName.setPosition(135, 100);
	SgameName.setScale(1.5f, 1);
	Texture restartGame;
	restartGame.loadFromFile("../pics/restart-image.jpg");
	Sprite SrestartGame(restartGame);
	SrestartGame.setPosition(125, 150);
	Music sound;
	sound.openFromFile("../music/start-music2.wav");
	sound.setVolume(50);
	Music sound2;
	sound2.openFromFile("../music/start-music.wav");
	sound2.setVolume(20);
	Music sound3;
	sound3.openFromFile("../music/loose-music.wav");
	Music sound4;
	sound4.openFromFile("../music/win-music.wav");
	for (i = 0; i <= 13; i++) {
		for (int j = 0; j <= 13; j++) {
			blocks[n].setTexture(block);
			blocks[n].setPosition(i * 43, j * 20);
			n++;
		}
	}//pour les blocks
	Texture win_image;
	win_image.loadFromFile("../pics/win-image.jpg");
	Sprite Swin_image(win_image);
	Swin_image.setPosition(150.0f, 150.0f);
	Swin_image.setScale(0.5f, 0.5f);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			}
		}
		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePosition = sf::Mouse::getPosition(window);
				Vector2f mousePositionFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
				if (startButtonSprite.getGlobalBounds().contains(mousePositionFloat)) {
					gameStarted = true;
					// start button est clique
					// On a commencé le jeu!
				}
			}
		}
		sound.setLoop(true);
		if (!gameStarted) {//start menu 
			if (!soundPlayed)
			{
				sound.play();
				soundPlayed = true;
			}
			window.draw(startButtonSprite);
			window.draw(SgameName);
			window.display();
		}
		sound2.setLoop(true);
		if (gameStarted) {//on est maintenant dans le jeu 
			scoreText.setString("Score: " + std::to_string(score));
			if (!sound2Played) {
				sound2.setPlayingOffset(seconds(0));
				sound2.play();
				sound2Played = true;
			}
			if (soundPlayed) {
				sound.pause();
				soundPlayed = false;
			}
			if (sound3Played) {
				sound3.pause();
				sound3Played = false;
			}
			Sball.move(dx, 0);//initialisation du position du ballon
			Sball.move(0, dy);
			for (int j = 0; j < n; j++) {
				if (isCollide(Sball, blocks[j]))
				{ //lorsque le ballon se coincide avec le block
					FloatRect blockBounds = blocks[j].getGlobalBounds();
					if (Sball.getPosition().y + Sball.getRotation() > blockBounds.top && Sball.getPosition().y - Sball.getRotation() < blockBounds.top + blockBounds.height)
					{
						dy = -dy;
					}
					else if (Sball.getPosition().x + Sball.getRotation() > blockBounds.left && Sball.getPosition().x - Sball.getRotation() < blockBounds.left + blockBounds.width)
					{
						dx = -dx;
					}
					blocks[j].setPosition(-100, 0);//faire disparaitre le block touchée
					score++;// incrémentation du score 
					scoreText.setString("Score: " + std::to_string(score));// affichage du score
				}
			}

			for (int j = 0; j < n; j++) {
				if (isCollide(Sball, blocks[j])) {
					FloatRect blockBounds = blocks[j].getGlobalBounds();
					if (Sball.getPosition().y + Sball.getRotation() > blockBounds.top && Sball.getPosition().y - Sball.getRotation() < blockBounds.top + blockBounds.height)
					{
						dy = -dy;
					}
					else if (Sball.getPosition().x + Sball.getRotation() > blockBounds.left && Sball.getPosition().x - Sball.getRotation() < blockBounds.left + blockBounds.width)
					{
						dx = -dx;
					}
					blocks[j].setPosition(-100, 0);
					score++;
					scoreText.setString("Score: " + std::to_string(score));
				}
			}
			Vector2f Vball = Sball.getPosition();
			if (Vball.x < 0 || Vball.x>600)dx = -dx;
			if (Vball.y < 0 || Vball.y>600)dy = -dy;
			//le ballon ne dépasse pas les limites de la fenètre 
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (Spaddle.getPosition().x + Spaddle.getGlobalBounds().width < window.getSize().x) {
					Spaddle.move(6, 0);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (Spaddle.getPosition().x > 0) {
					Spaddle.move(-6, 0);
				}
			}
			//le paddle ne dépasse pas les limtes de la fenètre

			if (isCollide(Spaddle, Sball)) dy = -(rand() % 5 + 2);//lorsque le ballon et le paddle se coincide 


			if (Sball.getPosition().y > Spaddle.getPosition().y) {
				ballLost = true;
			}
			//dans le cas ou le joueur perd le ballon
			if (ballLost && isCollide(Spaddle, Sball) == false)
				nbChance--;
			ballLost = false;
			//modifier la vitesse de ballon lorsque le joueur atteint un certain score
			if (score == 30)
				window.setFramerateLimit(65);
			if (score == 60)
				window.setFramerateLimit(70);
			if (score == 100)
				window.setFramerateLimit(85);
			if (score == 150)
				window.setFramerateLimit(90);
			if (score == n) {//lorque le joueur gagne 
				if (!sound4Played) {
					sound4.play();
					sound4Played = true;

				}
				if (sound2Played) {
					sound2.pause();
					sound2Played = false;
				}
				while (window.isOpen()) {

					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
						{
							window.close();
							return 0;
						}
					}

					window.clear();
					window.draw(Swin_image);
					window.display();

				}
			}
			//lorsque le joueur perd sa chance 
			if (nbChance == 0)
			{
				window.setFramerateLimit(60);
				if (!sound3Played) {
					sound3.setPlayingOffset(seconds(0));
					sound3.play();
					sound3Played = true;

				}
				if (sound2Played) {
					sound2.pause();
					sound2Played = false;
				}
				lose = true;
				while (lose)
				{
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
						{
							window.close();
							return 0;
						}
					}
					scoreText.setString("Score: " + std::to_string(score));
					window.clear();
					window.draw(SrestartGame);
					window.display();
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
						if (SrestartGame.getGlobalBounds().contains(mousePosF)) {
							// Réinisialisation ball, paddle, blocks,et score avec leurs positions et valeurs initiales
							Sball.setPosition(300.0f, 575.0f);
							Spaddle.setPosition(300.0f, 580.0f);
							score = 0;
							for (int i = 0; i < n; i++) {
								blocks[i].setPosition((i % 14) * 43, (i / 14) * 20);
							}
							ballLost = false;
							lose = false;
							nbChance = 1;
						}
					}
				}

			}
			window.clear();
			window.draw(Sbackground);
			window.draw(Sball);
			window.draw(Spaddle);
			window.draw(scoreText);
			for (int j = 0; j < n; j++) {
				window.draw(blocks[j]);
			}
			window.display();
		}

	}
	return 0;
}
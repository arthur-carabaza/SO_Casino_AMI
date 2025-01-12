CREATE DATABASE IF NOT EXISTS JuegoChat;
USE JuegoChat;

-- TABLA DE JUGADOR
CREATE TABLE Jugadores (
    id INT PRIMARY KEY AUTO_INCREMENT,  -- Identificador único del jugador
    usuario VARCHAR(50) NOT NULL UNIQUE, -- Nombre de usuario del jugador
    password VARCHAR(100) NOT NULL      -- Contraseña para iniciar sesión
);

-- TABLA DE SALAS
CREATE TABLE Salas (
    id INT PRIMARY KEY AUTO_INCREMENT,
	idS INT,
    fecha_creacion DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- TABLA DE PARTICIPANTES RELACION JUGADOR-SALA
CREATE TABLE Participantes (
    id INT PRIMARY KEY AUTO_INCREMENT,
    sala_id INT,
    usuario_id INT,
    FOREIGN KEY (sala_id) REFERENCES Salas(id) ON DELETE CASCADE,
    FOREIGN KEY (usuario_id) REFERENCES Jugadores(id) ON DELETE CASCADE
);

-- TABLA DE MENSAJES
CREATE TABLE Mensajes (
    id INT PRIMARY KEY AUTO_INCREMENT,
    sala_id INT,
    usuario_id INT,
    mensaje TEXT,
    fecha_envio DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (sala_id) REFERENCES Salas(id) ON DELETE CASCADE,
    FOREIGN KEY (usuario_id) REFERENCES Jugadores(id) ON DELETE CASCADE
);


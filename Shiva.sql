CREATE DATABASE IF NOT EXISTS M1_JuegoPoker;
USE M1_JuegoPoker;

-- Crear la tabla de jugadores
CREATE TABLE Jugadores (
    id INT PRIMARY KEY AUTO_INCREMENT,  -- Identificador único del jugador
    usuario VARCHAR(50) NOT NULL UNIQUE, -- Nombre de usuario del jugador
    dinero DECIMAL(10, 2) DEFAULT 0,    -- Dinero del jugador
    victorias INT DEFAULT 0,            -- Número de victorias del jugador
    partidas INT DEFAULT 0,             -- Número total de partidas jugadas por el jugador
    cartas VARCHAR(100),                -- Cartas que posee el jugador (guardadas como string por simplicidad)
    password VARCHAR(100) NOT NULL      -- Contraseña para iniciar sesión
);

-- Crear la tabla de cartas
CREATE TABLE Cartas (
    id INT PRIMARY KEY AUTO_INCREMENT,  -- Identificador único de la carta
    simbolo VARCHAR(10) NOT NULL,       -- Símbolo de la carta (picas, corazones, tréboles, diamantes)
    numero INT NOT NULL                 -- Número de la carta (1-13)
);

-- Crear la tabla de partidas
CREATE TABLE Partidas (
    id INT PRIMARY KEY AUTO_INCREMENT,  -- Identificador único de la partida
    id_jugador INT,                     -- ID del jugador (relacionado con la tabla Jugadores)
    dinero_apostado DECIMAL(10, 2),     -- Dinero apostado en la partida
    resultado VARCHAR(10),              -- Resultado de la partida ('ganó', 'perdió')
    FOREIGN KEY (id_jugador) REFERENCES Jugadores(id)
);

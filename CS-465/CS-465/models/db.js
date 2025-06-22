const mongoose = require('mongoose');
const readLine = require('readline');  // For Windows-specific handling
const host = process.env.DB_HOST || '127.0.0.1';  // Use environment variable or default to localhost
const dbURI = `mongodb://${host}:27017/travlr`;  // Default MongoDB port is 27017

// Function to connect with a small timeout
const connect = () => {
    setTimeout(() => {
        mongoose.connect(dbURI, { useNewUrlParser: true, useUnifiedTopology: true });
    }, 1000);  // 1-second delay before connecting
};

// Monitor connection events
mongoose.connection.on('connected', () => {
    console.log(`Mongoose connected to ${dbURI}`);
});

mongoose.connection.on('error', (err) => {
    console.log('Mongoose connection error: ', err);
});

mongoose.connection.on('disconnected', () => {
    console.log('Mongoose disconnected');
});

// Graceful shutdown function
const gracefulShutdown = (msg) => {
    mongoose.connection.close(() => {
        console.log(`Mongoose disconnected through ${msg}`);
    });
};

// Event listeners for graceful shutdowns
process.once('SIGUSR2', () => {
    gracefulShutdown('nodemon restart');
    process.kill(process.pid, 'SIGUSR2');
});

process.on('SIGINT', () => {
    gracefulShutdown('app termination');
    process.exit(0);
});

process.on('SIGTERM', () => {
    gracefulShutdown('app shutdown');
    process.exit(0);
});

// If running on Windows, handle SIGINT for graceful shutdown
if (process.platform === 'win32') {
    const r1 = readLine.createInterface({
        input: process.stdin,
        output: process.stdout
    });
    r1.on('SIGINT', () => {
        process.emit("SIGINT");
    });
}

// Make the initial connection to the DB
connect();

// Import the Mongoose schema (e.g., `travlr.js`)
require('./travlr');

module.exports = mongoose;

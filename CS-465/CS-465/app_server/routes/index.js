// app_server/index.js

const express = require('express');
const dotenv = require('dotenv');
const bodyParser = require('body-parser');
const authenticateController = require('../app_api/controllers/authenticate'); // adjust path if needed
const usersRoutes = require('../app_api/routes/users'); // if you have a users route file

dotenv.config();

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true }));

// Routes
app.post('/login', authenticateController.login); // login route

// Start server
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

module.exports = app;
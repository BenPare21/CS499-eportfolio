const mongoose = require('mongoose');
require('./travlr'); // Imports the schema/model

const dbURI = 'mongodb://localhost:27017/travlr'; // adjust port/name if needed

mongoose.connect(dbURI, { useNewUrlParser: true, useUnifiedTopology: true });

mongoose.connection.on('connected', () => {
  console.log(`Mongoose connected to ${dbURI}`);
});

mongoose.connection.on('error', err => {
  console.log('Mongoose connection error:', err);
});

mongoose.connection.on('disconnected', () => {
  console.log('Mongoose disconnected');
});

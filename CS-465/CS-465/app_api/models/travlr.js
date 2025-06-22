const mongoose = require('mongoose');

const tripSchema = new mongoose.Schema({
  code: { type: String, required: true },
  name: { type: String, required: true },
  length: { type: String },
  start: { type: Date },
  resort: { type: String },
  perPerson: { type: String },
  image: { type: String },
  description: { type: String }
});

mongoose.model('Trip', tripSchema);

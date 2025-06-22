// did get rid of some stuff very similiar btw

var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan')
const hbs = require("hbs");

//Define routers 
var indexRouter = require('./app_server/routes/index');
var usersRouter = require('./app_server/routes/index');
var travelRouter = require('./app_server/routes/index');
var apiRouter = require('./app_server/routes/index');

var handlebars = require('hbs');

const indexRouter = require("./routes/index");
const userRouter = require("./routes/user");


//Bring in the database
require('./app_api/models/db')

var app = express()

app.set('views', path.join(_dirname,'app_server','views'));

handlebars.registerPartials(_dirname+ 'app_server/views/partials')

// Set view engine to Handlebars
app.set("view engine", "hbs");

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({extended: false}))
app.use(cookieParser());
app.use(express.static(path.join(_dirname, 'public')))

//wire up routes to controllers
app.use('/', indexRouter);
app.use('users', usersRouter);
app.use('/travel',travelRouter);
app.use('.api',apiRouter);


app.set("views", path.join(__dirname, "views"));

// Register partials
hbs.registerPartials(path.join(__dirname, "views/partials"));

// Middleware
app.use(express.static(path.join(__dirname, "public")));
app.use("/", indexRouter);
app.use("/user", userRouter);

// Listen on port 3000
app.listen(3000, () => {
  console.log("Server is running on http://localhost:3000");
});

module.exports = app;

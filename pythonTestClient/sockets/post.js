// grab the packages we need
var express = require('express');
var app = express();
var port = process.env.PORT || 8090;
var qs = require('querystring')
// routes will go here

// start the server
app.listen(port);
console.log('Server started! At http://localhost:' + port);


app.post('/', function (req, res) {
    //res.send('POST request to the homepage')
    //console.log("got a thing")
   // console.log(req)
    var body = ""
    req.on("data",function(data){
        body+=data
       //req.connection.destory()
        //console.log(qs.parse(body))
    })
    req.on('end', function(){
        //var post = qs.parse(body)
        //console.log(post.key)
        console.log(qs.parse(body).text)
        res.end()
    })
})
http = require('http');
express = require('express');
app = express();
server = http.createServer(app)
io = require('socket.io').listen(server);
MongoClient = require('mongodb').MongoClient;
bodyParser = require('body-parser')

app.use(bodyParser.urlencoded({
    extended: true
}));

app.use(bodyParser.json());

MongoClient.connect("mongodb://localhost:27017/cntrlr", function(err, db) {

  console.log("Connected correctly to server.");
 // db.close();


io.on('connection', function(socket){
    console.log("connection");

    
    socket.on('login', function(msg){
        user = msg.username;
        pass = msg.password;
        //console.log(user+",,,,"+pass)
        db.collection('users').findOne( { username:user, password:pass},function(error,result){
            if(result){
                
                /*
                code=Math.random();
                db.collection('users').update(
                    {username:user, password:pass},
                    { $set:{"auth":code}},
                function(error,result){
                    //console.log(result);
                    socket.emit("code",{"code":code});
                });
                */
                socket.emit("code",{"code":result.auth});
            }else{
                console.log("invalid");
                socket.emit("code","fuck you");
            }
        });


        
    });

    socket.on("join",function(msg){
        socket.join(msg);

        io.to(msg).emit('toast', 'JOINED');
    });

/*
    //message,16302453822,It Works!
    stdin = process.openStdin();
    stdin.addListener("data", function(d) {
        //console.log("ddd");
       m=d.toString().trim().split(",");
       socket.emit(m[0], {"number":m[1],"content":m[2]});
    });*/



});

//db.collection('users').insertOne( { username:"cntlr", password:"admin"},function(error,result){});


    app.post('/getMessage',function(req,res){

        console.log("get msg");
        key = req.body.key;
        io.to(key).emit('getMessage', {});

        socket.on('resp', function(msg){
            console.log("RESP!!!");
            res.send(msg);
        });

    

    });

app.post('/handle',function(req,res){
    
    //console.log("dwwdw");

    user = req.body.user;
    pass = req.body.pass;

    console.log(req.body)

    console.log(user);

    res.send(user+","+pass);
});


app.post('/signup',function(req,res){
    user = req.body.username;
    pass = req.body.password;
    email = req.body.email;

     db.collection('users').insert( { username:user, password:pass,email:email},function(error,result){
         res.send('OK!');
     });
});

app.post('/message',function(req,res){
    key = req.body.key;
    number = req.body.number;
    content = req.body.content;

   // console.log("KEY: "+key);
    io.to(key).emit('message', {number:number,content:content});
    res.send('OK');
});

app.post('/music',function(req,res){
    key = req.body.key;
    action =  req.body.action;
    
    io.to(key).emit('music', {action:action});
    res.send('OK');
});



//text 
app.post('/login',function(req,res){
    user = req.body.username;
    pass = req.body.password;
    //console.log(user+",,,,"+pass)
    db.collection('users').findOne( { username:user, password:pass},function(error,result){
        if(result){
            

            
            code=Math.random()+"";
            code=code.replace("0.","");
            db.collection('users').update(
                {username:user, password:pass},
                { $set:{"auth":code}},
            function(error,result){
                //console.log(result);
                res.send('{"code":"'+code+'"}');
            });
            
           // res.send('{"code":"'+result.auth+'"}');

        }else{
            console.log("invalid");
            res.send("invalid user or pass!");
        }
    });
});


server.listen(8090,function(){
    console.log('Server listening on port 8090!')
});

});

var config = {
    apiKey: "AIzaSyD6SW3dXUoa8zvbiGlaMUI7m010wjvb9Uk",
    authDomain: "test-2801d.firebaseapp.com",
    databaseURL: "https://test-2801d.firebaseio.com",
    projectId: "test-2801d",
    storageBucket: "test-2801d.appspot.com",
    messagingSenderId: "614998333367"
    };
firebase.initializeApp(config);

var database = firebase.database();

// write functions
  function writedata(){
    var value1=document.getElementById("id1").value;
    firebase.database().ref('Datawrite').set({
      infoID:"dataID",
      info1:"data",
      info2:"time",
      info3:value1
    });
  }


  function writeNewPost() {
    // A post entry.
    var value1=document.getElementById("id1").value;
    var value2=document.getElementById("time").value;
    var value3=document.getElementById("date").value;
    var value4=document.getElementById("gpsx").value;
    var value5=document.getElementById("gpsy").value;
    var postData = {
        value1: value1,
        value2: value2,
        value3: value3,
        value4: value4,
        value5: value5
      };
      // Get a key for a new Post.
    var newPostKey = firebase.database().ref().child('Datawrite').push().key;
    // Write the new post's data simultaneously in the posts list and the user's post list.
    var updates = {};
    updates['/Datawrite/' + newPostKey] = postData;
    updates['/user-posts/' /*+ value1 + '/' */+ newPostKey] = postData;
    return firebase.database().ref().update(updates);
  }

    //document.getElementById("v").showgetelement();

    function showgetelement(){
      var v=document.getElementById("v").value;
      console.log(v);
    }



    var checknewpost =  firebase.database().ref("user-posts/");
    function checkupdate(){
      checknewpost.on("child_changed",function(data){
        var updatedata=data.val();
        console.log("ID: " + post.value1);
        console.log("time: " + post.value2);
        console.log("date: " + post.value3);
        console.log("gpsx: " + post.value4);
        console.log("gpsy: " + post.value5);},
      )};



      var checkposts = firebase.database().ref("user-posts/");
      function checkdata(){
      checkposts.once("child_added", function(data,prevChildKey) {
        var post = data.val();
        document.getElementById("position").innerHTML=post.position;
        document.getElementById("averagepm25").innerHTML=post.averagepm25;
        document.getElementById("degree").innerHTML=post.degree;
        /*
        document.getElementById("Lat").innerHTML=post.lat;
        document.getElementById("lng").innerHTML=post.lng;
        document.getElementById("sender").innerHTML=post.sender;
        document.getElementById("time").innerHTML=post.timestamp;
        document.getElementById("weight").innerHTML=post.weight;*/
        console.log("Previous post: " + prevChildKey);},
      function (error) {
        console.log("Error: " + error.code);
      });
    }
    function ShowAnswer(){
       document.getElementById("AnswerBox").innerHTML=post.weight;
    }

    var checkall_data = firebase.database().ref();
    function checkall(){
      checkall_data.on("value",function(snapshot){
        document.getElementById("alldata").innerText=snapshot.val();
        console.log(snapshot.val().count);
      });

    }
    function attachdata(){
      var table = document.getElementById('displayData');
      dbRefObject = firebase.database().ref().child('user-posts' );
      dbRefObject.once('value', snap => {
      data = snap.val();
      for(var r in data) {
          var row = table.insertRow(-1);
          for(var c in data[r]) {
            cell = row.insertCell(-1);
            cell.innerHTML = data[r][c];
          }
      }

    });
    }
    document.getElementById("submitButton").addEventListener("click", myFunction);

    function myFunction() {
        document.getElementById('submitButton').disabled = true;
    }

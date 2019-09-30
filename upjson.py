from firebase import firebase

# from firebase.firebase import FirebaseApplication
# firebase = firebase.FirebaseApplication('https://myapp.firebaseio.com/', 
# None)
# result = firebase.get('/messages', None)
# from firebase.firebase import FirebaseApplication

test = {"A_positsion": "buildingsne", "degree": "great","averagepm25": "6.046586",}


url = "https://test-2801d.firebaseio.com/"

fb = firebase.FirebaseApplication(url , None)

fb.post("/user-posts",test)
print("{}OK".format(test))
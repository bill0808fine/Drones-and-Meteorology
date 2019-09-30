import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

# 引用私密金鑰
# path/to/serviceAccount.json 請用自己存放的路徑
cred = credentials.Certificate('/Users/chien/Desktop/data.json')

# 初始化firebase，注意不能重複初始化
firebase_admin.initialize_app(cred)

# 初始化firestore
db = firestore.client()

doc = {
  'name': "帽子哥",
  'email': "abc@gmail.com"
}

# 建立文件 必須給定 集合名稱 文件id
# 即使 集合一開始不存在 都可以直接使用

# 語法
# doc_ref = db.collection("集合名稱").document("文件id")

doc_ref = db.collection("pyradise_students").document("student_01")

# doc_ref提供一個set的方法，input必須是dictionary

doc_ref.set(doc)

'''
<script src="https://www.gstatic.com/firebasejs/5.2.0/firebase.js"></script>
<script>
  // Initialize Firebase
  var config = {
    apiKey: "AIzaSyD6SW3dXUoa8zvbiGlaMUI7m010wjvb9Uk",
    authDomain: "test-2801d.firebaseapp.com",
    databaseURL: "https://test-2801d.firebaseio.com",
    projectId: "test-2801d",
    storageBucket: "test-2801d.appspot.com",
    messagingSenderId: "614998333367"
  };
  firebase.initializeApp(config);
</script>
'''
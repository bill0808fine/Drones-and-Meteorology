import json, codecs , string ,time
from firebase import firebase

url = "https://test-2801d.firebaseio.com/"
fb = firebase.FirebaseApplication(url , None)


def Position(lat , lng):
	if   ( (22.627723 > float(lat) >= 22.627068) and (120.265446 <= float(lng) < 120.266026) ):
		return 'library'
	elif ( (22.626041 > float(lat) >= 22.625665) and (120.265512 <= float(lng) < 120.266008) ):
		return 'officebuilding'
	elif ( (22.627787 > float(lat) >= 22.625375) and (120.265072 <= float(lng) < 120.265512) ):
		return 'deptsnm'
	elif ( (22.627687 > float(lat) >= 22.626852) and (120.266734 <= float(lng) < 120.267671) ):
		return 'buildingsne'
	elif ( (22.626756 > float(lat) >= 22.626019) and (120.266738 <= float(lng) < 120.267125) ):
		return 'deptsec'
	elif ( (22.628955 > float(lat) >= 22.627770) and (120.267364 <= float(lng) < 120.268924) ):
		return 'dormtsuihen'
	elif ( (22.631402 > float(lat) >= 22.628847) and (120.263311 <= float(lng) < 120.264328) ):
		return 'dormwulin'
	else:
		return 'NSYSU'

def get_pmdegree(pm25):
	if float(pm25)<10:
		return 'great'
	elif 10<=float(pm25)<25:
		return 'normal'
	else :
		return 'serious'


while(1):
	# print('hello')
	try:
		print('\n')
		f = open('data.txt','rt')
		time.sleep(5)
		a = {}
		pretext = f.readlines()[0]

		pm25= pretext[pretext.find(':')  +1 : pretext.find(',')-1]
		lat = pretext[pretext.find('lat')+4 : pretext.find('lat')+13]
		lng = pretext[pretext.find('lng')+4 : pretext.find('lng')+15]
		now = time.strftime("%H.%M.%S")

		message = 'A_positsion:'+ Position(lat,lng) +','+pretext[:22]+'degree:'+get_pmdegree(pm25)+',time:'+now

		'''from message get single data '''
		v = message.strip('\n') #remove \n

		for x in v.split(','): #Separate by ',' between two items
			# print(x)
			g = x.strip().split(':')#strip() remove space , Separate by ':' between two items
			#g is list
			a[g[0]] = g[1]
			# a[g[0]] = float(g[1])

		'''dict:a匯出成json檔。'''
		json_str = json.dumps(a)
		data = json.loads(json_str) #data is json type
		###################
		print(data)
		fb.post("/user-posts",data)
		print("{}OK".format(test))

	except:
		time.sleep(1)


f.close()



# Reading data back
with open('data.json', 'r') as f:
    data = json.load(f)

print(data)


f.close()



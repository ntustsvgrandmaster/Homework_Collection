import sklearn as sk
import pandas as pd
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

csv_movie = pd.read_csv('ir_bx_all.csv')
all_movie = pd.DataFrame(csv_movie)

#rating函式主要是把評分的部分分群，根據每1/3*滿分分成低中高分3個群

def rating_cluster(row):
    if(row["audience_avg_rating"] == 0):
        if(row["imdb_score"] >= 6.6):
           return 2
        elif((row["imdb_score"] < 6.6) & (row["imdb_score"] >= 3.3)):
           return 1
        elif((row["imdb_score"] < 3.3)):
           return 0
    elif(row["audience_avg_rating"] >= 3.33):
        return 2
    elif(row["audience_avg_rating"] >= 1.66):
        return 1
    elif(row["imdb_score"] > 1.66):
        return 0
#

#對score_sentiment做處理
all_movie.fillna({'score_sentiment':0})
def sentiment_score(row):
    if(row['score_sentiment'] == 'POSITIVE'):
        return 1
    elif(row['score_sentiment'] == 'NEGATIVE'):
        return -1
    else:
        return 0

all_movie['number_score_sentiment'] = all_movie.apply(sentiment_score, axis = 1)
#

#對演員的分數做處理，如果兩邊都是null值的話就不管了，到時候也用不到
all_movie = all_movie.fillna({'actor1_score_imdb_actScore':0, 'actor2_score_imdb_actScore':0, 'actor3_score_imdb_actScore':0,
                              'actor1_score_tomaAudience_actScore':0, 'actor2_score_tomaAudience_actScore':0, 'actor3_score_tomaAudience_actScore':0})

def imdb_actor_audience_score1(row):
    if(row['actor1_score_imdb_actScore'] == 0): #後面的判斷條件似乎可以去掉，不過先把bug處理完再試吧
        return row['actor1_score_tomaAudience_actScore'] / 2
    else:
        return row['actor1_score_imdb_actScore']
def tomato_actor_audience_score1(row):
    if(row['actor1_score_tomaAudience_actScore'] == 0):
        return row['actor1_score_imdb_actScore'] * 2
    else:
        return row['actor1_score_tomaAudience_actScore']

def imdb_actor_audience_score2(row):
    if(row['actor2_score_imdb_actScore'] == 0):
        return row['actor2_score_tomaAudience_actScore'] / 2
    else:
        return row['actor2_score_imdb_actScore']
def tomato_actor_audience_score2(row):
    if(row['actor2_score_tomaAudience_actScore'] == 0):
        return row['actor2_score_imdb_actScore'] * 2
    else:
        return row['actor2_score_tomaAudience_actScore']

def imdb_actor_audience_score3(row):
    if(row['actor3_score_imdb_actScore'] == 0):
        return row['actor1_score_tomaAudience_actScore'] / 2
    else:
        return row['actor3_score_imdb_actScore']
def tomato_actor_audience_score3(row):
    if(row['actor3_score_tomaAudience_actScore'] == 0):
        return row['actor3_score_imdb_actScore'] * 2
    else:
        return row['actor3_score_tomaAudience_actScore']

all_movie['new_actor1_score_imdb_actScore'] = all_movie.apply(imdb_actor_audience_score1, axis = 1)
all_movie['new_actor2_score_imdb_actScore'] = all_movie.apply(imdb_actor_audience_score2, axis = 1)
all_movie['new_actor3_score_imdb_actScore'] = all_movie.apply(imdb_actor_audience_score3, axis = 1)

all_movie['new_actor1_score_tomaAudience_actScore'] = all_movie.apply(tomato_actor_audience_score1, axis = 1)
all_movie['new_actor2_score_tomaAudience_actScore'] = all_movie.apply(tomato_actor_audience_score2, axis = 1)
all_movie['new_actor3_score_tomaAudience_actScore'] = all_movie.apply(tomato_actor_audience_score3, axis = 1)
#

#如果有3個演員的話，分數就按照{0.4,0.3,0.3}的比例去分配，2個的話則是{0.6,0.4}，一個是{1}
def total_imdb_actor_score(row):
    if(row['new_actor3_score_imdb_actScore'] == 0):
        if(row['new_actor2_score_imdb_actScore'] == 0):
            return row['new_actor1_score_imdb_actScore']
        else:
            return row['new_actor1_score_imdb_actScore'] * 0.6 + row['new_actor2_score_imdb_actScore'] * 0.4
    else:
        return row['new_actor1_score_imdb_actScore'] * 0.4 + row['new_actor2_score_imdb_actScore'] * 0.3 + row['new_actor3_score_imdb_actScore'] * 0.3

def total_tomato_actor_score(row):
    if(row['new_actor3_score_tomaAudience_actScore'] == 0):
        if(row['new_actor2_score_tomaAudience_actScore'] == 0):
            return row['new_actor1_score_tomaAudience_actScore']
        else:
            return row['new_actor1_score_tomaAudience_actScore'] * 0.6 + row['new_actor2_score_tomaAudience_actScore'] * 0.4
    else:
        return row['new_actor1_score_tomaAudience_actScore'] * 0.4 + row['new_actor2_score_tomaAudience_actScore'] * 0.3 + row['new_actor3_score_tomaAudience_actScore'] * 0.3
all_movie['total_imdb_actor_score'] = all_movie.apply(total_imdb_actor_score, axis = 1)
all_movie['total_tomato_actor_score'] = all_movie.apply(total_tomato_actor_score, axis = 1)
#

#處理rating(1)的部分，先補0後把各個rate以0~15種做分類
all_movie = all_movie.fillna({'rating':0})

def number_rating(row):
    if(row['rating'] == 'NR'):
        return 1
    elif(row['rating'] == 'G'):
        return 2
    elif(row['rating'] == 'R'):
        return 3
    elif(row['rating'] == 'PG-13'):
        return 4
    elif(row['rating'] == 'PG'):
        return 5
    elif(row['rating'] == 'TV-MA'):
        return 6
    elif(row['rating'] == 'TV-14'):
        return 7
    elif(row['rating'] == 'M'):
        return 8
    elif((row['rating'] == 'NC-17') or (row['rating'] == 'NC17')):
        return 9
    elif(row['rating'] == 'X'):
        return 10
    elif(row['rating'] == 'TV-PG'):
        return 11
    elif(row['rating'] == 'TV-G'):
        return 12
    elif(row['rating'] == 'TV-Y7'):
        return 13
    elif(row['rating'] == 'TV-7'):
        return 14
    elif(row['rating'] == 'GP'):
        return 15
    else:
        return 0

all_movie['new_rating1'] = all_movie.apply(number_rating, axis = 1)
#

#處理imdb和tomato的導演評分的部分，缺失值就用中位數來補。
drop4_movie = all_movie.loc[:,"imdb_dirScore"].dropna()
drop5_movie = all_movie.loc[:,"tomato_dirScore"].dropna()
imdb_dirS = drop4_movie.median() #取得中位數
tomato_dirS = drop5_movie.median()

all_movie = all_movie.fillna({"imdb_dirScore":imdb_dirS, "tomato_dirScore":tomato_dirS})

def new_imdb_dirS(row):
    if(row["imdb_dirScore"] == 0):
        if(row["tomato_dirScore"] == 0):
            return imdb_dirS
        else:
            return row["tomato_dirScore"] * 2
    else:
        return row["imdb_dirScore"]

def new_tomato_dirS(row):
    if(row["tomato_dirScore"] == 0):
        if(row["imdb_dirScore"] == 0):
            return tomato_dirS
        else:
            return row["imdb_dirScore"] / 2
    else:
        return row["tomato_dirScore"]

all_movie['new_imdb_dirS'] = all_movie.apply(new_imdb_dirS, axis = 1)
all_movie['new_tomato_dirS'] = all_movie.apply(new_tomato_dirS, axis = 1)
#

#12~15，因為空缺的值不多，總之就是先用中位數來補。如果不需要不要管就好(?)
drop12_movie = all_movie.loc[:,"tomatometer_rating"].dropna()
drop13_movie = all_movie.loc[:,"tomatometer_count"].dropna()
drop14_movie = all_movie.loc[:,"audience_rating"].dropna()
drop15_movie = all_movie.loc[:,"audience_count"].dropna()

me12 = drop12_movie.median()
me13 = drop13_movie.median()
me14 = drop14_movie.median()
me15 = drop15_movie.median()

all_movie = all_movie.fillna({"tomatometer_rating":me12, "tomatometer_count":me13, "audience_rating":me14, "audience_count":me15})
#

#19,24,29,34用補0的方式做，可以考慮要不要全部加在一起。
all_movie = all_movie.fillna({"director_facebook_likes":0, "actor_1_facebook_likes":0, "actor_2_facebook_likes":0, "actor_3_facebook_likes":0,
                              "movie_facebook_likes":0, "cast_total_facebook_likes":0})
#


all_movie = all_movie.fillna({"audience_avg_rating":0}) #先補0試試，不行再看看平均數/中位數
all_movie["target"] = all_movie.apply(rating_cluster,axis = 1)

#把23, 28, 33, 38, 41除了38補0以外
drop38 = all_movie.loc[:,"imdb_num_user_for_reviews"].dropna()
drop41 = all_movie.loc[:,"budget"].dropna()
all_movie = all_movie.fillna({"imdb_num_user_for_reviews":drop38.median(), "budget":drop41.median()})
#


all_movie = all_movie.dropna(subset = {"target"})
print(all_movie.info())
movie_data = all_movie.loc[:,{"new_rating1","total_imdb_actor_score","total_tomato_actor_score","new_imdb_dirS","new_tomato_dirS","tomatometer_rating",
                           "tomatometer_count","audience_rating","audience_count","director_facebook_likes","actor_1_facebook_likes","actor_2_facebook_likes",
                           "actor_3_facebook_likes","movie_facebook_likes","cast_total_facebook_likes",'number_score_sentiment'}]
movie_label = all_movie.loc[:,"target"]

train_data , test_data , train_label , test_label = train_test_split(movie_data,movie_label,test_size=0.2)

knn = KNeighborsClassifier()
knn.fit(train_data, train_label)

predict_data = knn.predict(test_data)
print(accuracy_score(test_label, predict_data))
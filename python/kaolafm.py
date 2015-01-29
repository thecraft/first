# -*- coding: utf-8 -*-  
import urllib
import urllib2
import md5
import os

appid = ''
secretKey = ''
device_id = ''
openid = ''
base_url = 'http://open.kaolafm.com/v1/app/' 

get_method = 'get'
post_method = 'post'

def get_sign(method, url, appid, secretKey):
    param_list = [method, url, appid, secretKey]
    param_str = ''.join(param_list).encode('utf-8')
    #print param_str
    sign_raw = urllib.quote(param_str, safe='').lower()
    print 'RawSign:' + sign_raw
    sign = md5(sign_raw)
    return sign

def md5(str):
    import hashlib
    m = hashlib.md5()   
    m.update(str)
    return m.hexdigest()

def post_request(url, values):
    data = urllib.urlencode(values)

    req = urllib2.Request(url, data)
    response = urllib2.urlopen(req)

    the_page = response.read()
    print 'resp:'
    print the_page

def get_request(url, values):
    real_url = url + '?'

    for item in values:
        real_url += item + '='
        real_url += values[item] + '&'

    real_url = real_url.rstrip('&')
    print real_url
    req = urllib2.Request(real_url)
    response = urllib2.urlopen(req)
    the_page = response.read()
    print 'resp:' 
    print the_page

#1 激活当前设备
def test_active():
    active_url = base_url + 'active'
    this_url = active_url
    sign = get_sign(post_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['deviceid'] = device_id
    post_request(this_url, values)

#2 应用初始化
def test_init():
    init_url = 'http://open.kaolafm.com/v1/app/init'
    this_url = init_url 
    sign = get_sign(post_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['deviceid'] = device_id
    values['devicetype'] = '0'
    values['osversion'] = 'android5.0'
    values['network'] = '1'
    post_request(this_url, values)

#3 获取指定分类下列表 
def test_sublist():
    sublist_url = 'http://open.kaolafm.com/v1/category/sublist'
    this_url = sublist_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    get_request(this_url, values)

#4 获取指定分类下内容
def test_list():
    list_url = 'http://open.kaolafm.com/v1/content/list'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    values['cid'] = '704'
    get_request(this_url, values)

#5 索指定关键字内容
def test_search():
    list_url = 'http://open.kaolafm.com/v1/content/search'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    values['q'] = '新闻'
    get_request(this_url, values)

#6 获取专辑详情
def test_album():
    list_url = 'http://open.kaolafm.com/v1/album/get'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    values['aid'] = '1100000000134'
    get_request(this_url, values)

#7 获取指定专辑下期列表
def test_audiolist():
    list_url = 'http://open.kaolafm.com/v1/audio/list'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid 
    #专辑ID
    values['aid'] = '1100000000134'
    get_request(this_url, values)

#8 获取电台详情
def test_radio_get():
    list_url = 'http://open.kaolafm.com/v1/radio/get'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    #电台ID
#    values['rid'] = '1200000000199'
    values['rid'] = '1200000000210'

    get_request(this_url, values)


#9 获取指定电台播单列表
def test_radio_playlist():
    list_url = 'http://open.kaolafm.com/v1/radio/playlist'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    #电台ID
#    values['rid'] = '1200000000199'
    values['rid'] = '1200000000210'

    get_request(this_url, values)

#10 获取指定期详情
def test_audio_get():
    list_url = 'http://open.kaolafm.com/v1/audio/get'
    this_url = list_url
    sign = get_sign(get_method, this_url, appid, secretKey)

    values = {}
    values['sign'] = sign
    values['appid'] = appid
    values['openid'] = openid
    #期ID
    values['aid'] = '1000000767984'

    get_request(this_url, values)

if __name__ == '__main__':
    #test_active()
    #test_init()
    #test_sublist()
    #test_list()
    #test_search()
    #test_album()
    #test_audiolist()
    #test_radio_get()
    #test_radio_playlist()
    test_audio_get()



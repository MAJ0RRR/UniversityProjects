<?php

use MongoDB\BSON\ObjectID;

function get_db()
{
    $mongo = new MongoDB\Client(
        "mongodb://localhost:27017/wai",
        [
            'username' => 'wai_web',
            'password' => 'w@i_w3b',
        ]);

    $db = $mongo->wai;

    return $db;
}

function add_photo($photo){
    $db = get_db();

    return $db->photos->insertOne($photo);
}

function get_photos($page){
    $db = get_db();

    $pageSize = 9;
    $opts = [
        'skip' => ($page - 1) * $pageSize,
        'limit' => $pageSize
    ];

    $photos =  $db->photos->find([],$opts);
    return $photos;
}


function create_user($user){
    $db = get_db();

    $exist = count($db->users->find(['login' => $user['login']])->toArray());

    if($exist){
        return false;
    }
    else{
     return $db->users->insertOne($user);
    }
}

function login_user($user){
    $db = get_db();

    $exist = count($db->users->find(['login' => $user['login']])->toArray());

    if($exist){
        $current_user = $db->users->findOne(['login' => $user['login']]);
        if(password_verify($user['password'],$current_user['password'])){
            // set session id
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

function get_user_id($user){
    $db = get_db();

    $current_user = $db->users->findOne(['login' => $user['login']]);
    return $current_user['_id'];
}




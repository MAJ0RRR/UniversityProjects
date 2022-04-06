<?php
require_once 'business.php';
require_once 'controller_utils.php';

function index(&$model){
    return 'index_view';
}

function postacie(&$model){
    return 'postacie_view';
}

function epoki(&$model){
    return 'epoki_view';
}

function kontakt(&$model){
    return 'kontakt_view';
}

function quiz(&$model){
    return 'quiz_view';
}

function upload(&$model){
    if($_SERVER['REQUEST_METHOD'] === 'POST'){

        $upload_dir = '/var/www/prod/src/web/static/images/upload/';
        $file = $_FILES['photo'];
        $file_size = $file['size'];
        $tmp_path = $file['tmp_name'];

        $file_info = finfo_open(FILEINFO_MIME_TYPE);
        $file_name = $_FILES['photo']['tmp_name'];
        $mime_type = finfo_file($file_info, $file_name);
        $ext = explode('/', $mime_type)[1];

        require 'core.php';

        if ($mime_type === 'image/jpeg' || $mime_type === 'image/png') {
            if ($file_size <= 1000000) {

                $author = $_POST['author'];
                $title = $_POST['title'];

                $photo = [
                    'author' => $author,
                    'title' => $title,
                    'ext' => $ext,
                ];

                if(add_photo($photo)){
                    $model['photo'] = $photo;
                    $target = $upload_dir . 'photos/'.$author.$title.'_original.'.$ext;
                    if(move_uploaded_file($tmp_path, $target)){
                        create_watermarked_image($mime_type, $target, $upload_dir,$photo);
                        create_miniature($mime_type, $target, $upload_dir,$photo);
                        return 'redirect:view_gallery';
                    }
                    else{
                        setcookie('error','There was a problem with uploading your photo to our server,try again',time() + (86400 * 30),'/error');
                        return 'redirect:error';
                    }
                }

                else{
                    setcookie('error','Something went wrong when adding photo to data base,try again',time() + (86400 * 30),'/error');
                    return 'redirect:error';
                }
            }
            else {
                setcookie('error','File is bigger than 1 MB,try again',time() + (86400 * 30),'/error');
                return 'redirect:error';
            }
        }
        else {
            if($file_size <= 1000000){
                setcookie('error','File is not of supported type (png or jpeg only),try again',time() + (86400 * 30),'/error');
                return 'redirect:error';
            }
            else{
                setcookie('error','File is not of supported type(png or jpeg only) and it is too big (over 1 MB)',time() + (86400 * 30),'/error');
                return 'redirect:error';
            }

        }
    }
    else{
        setcookie('error','You have to use form to send the file,try again',time() + (86400 * 30),'/error');
        return 'redirect:error';
    }
}

function view_gallery(&$model){
    if(!isset($_GET['page'])){
        $page=1;
    }
    else{
        $page = $_GET['page'];
        if($page > 10){
            $page = 1;
        }
        else if($page < 1){
            $page = 10;
        }
    }

    $photos = get_photos($page);
    $model['photos'] = $photos;
    $model['page'] = $page;

    return 'gallery_view';
}

function register(&$model){
    if($_SERVER['REQUEST_METHOD'] === 'GET'){
        return 'register_view';

    }
    if($_SERVER['REQUEST_METHOD'] === 'POST') {
        $login = $_POST['login'];
        $password = $_POST['password'];
        $email = $_POST['email'];
        $repeat_password = $_POST['repeat_password'];
        $valid = TRUE;

        $vars = array('login','password','email','repeat_password');

        foreach($vars as $v) {
            if(!isset($_POST[$v]) || empty($_POST[$v])) {
                $valid = FALSE;
                break;
            }
        }

        if ($valid) {
            if ($password === $repeat_password) {
                $hash = password_hash($password,PASSWORD_DEFAULT);
                $user = [
                    'login' => $login,
                    'password' => $hash,
                    'email' => $email,
                ];
                if(create_user($user)){
                    return 'redirect:success';
                }
                else{
                    return 'redirect:fail';
                }
            }
            else return 'redirect:fail';
        }
        else return 'redirect:fail';
        }
    }

function login(&$model){
    if($_SERVER['REQUEST_METHOD'] === 'GET'){
        return 'login_view';
    }
    if($_SERVER['REQUEST_METHOD'] === 'POST'){
        $login = $_POST['login'];
        $password = $_POST['password'];
        $valid = TRUE;

        $vars = array('login','password');

        foreach($vars as $v) {
            if(!isset($_POST[$v]) || empty($_POST[$v])) {
                $valid = FALSE;
                break;
            }
        }

        if($valid){
            $user = [
                'login' => $login,
                'password' => $password,
            ];
            if(login_user($user)){
                $_SESSION['session_id'] = get_user_id($user);
                session_regenerate_id();
                $_SESSION['name'] = $user['login'];
                $_SESSION['logged'] = 'yes';
                return 'redirect:success';
            }
            else{
                return 'redirect:fail';
            }
        }
        else{
            return 'redirect:fail';
        }
    }
}

function error(&$model){
    return 'error_view';
}

function success(&$model){
    return 'success_view';
}

function fail(&$model){
    return 'fail_view';
}

function logout(&$model){
    session_destroy();

    $params = session_get_cookie_params();
    setcookie(session_name(), '', time() - 42000,
        $params["path"], $params["domain"],
        $params["secure"], $params["httponly"]
    );

    return 'logout_view';
}

function save_photos(&$model){
    if ($_SERVER['REQUEST_METHOD'] === 'POST' && !empty($_POST['saved_photo'])) {
        $saved = $_POST['saved_photo'];
        $my_photos = &get_saved();
        $index = 0;
        foreach ($saved as $photo) {
            $my_photos[$index] = $photo;
            $index++;
        }
        $model['photo'] = $my_photos;
        return 'redirect:my_photos';
    }
    else{
        setcookie('error','Nie zapisano żadnych zdjęć!',time() + (86400 * 30),'/error');
        return 'redirect:error';
    }
}

function my_photos(&$model){

    if(!isset($_GET['page'])){
        $page=1;
    }
    else{
        $page = $_GET['page'];
        if($page > 10){
            $page = 1;
        }
        else if($page < 1){
            $page = 10;
        }
    }

    $photos = &get_saved();
    $model['photos'] = $photos;
    $model['page'] = $page;

    return 'my_photos_view';
}


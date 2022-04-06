<?php

function open_image($mime_type,$target){
    switch($mime_type){
        case 'image/jpeg':
            $img = imagecreatefromjpeg($target);
            break;
        case 'image/png':
            $img = imagecreatefrompng($target);
            break;
    }
    return $img;
}

function save_image($mime_type,$upload_dir,$img,$name){
    switch($mime_type){
        case 'image/jpeg':
            imagejpeg($img,$upload_dir.$name.".jpeg");
            break;
        case 'image/png':
            imagepng($img,$upload_dir.$name.".png");
            break;
    }
    imagedestroy($img);
}

function create_watermarked_image($mime_type,$target,$upload_dir,$photo){ // Apply watermark to existing image and save it
    $watermark = $_POST['watermark'];
    $font = '/var/www/prod/src/web/static/fonts/Roboto-Bold.ttf';

    $img = open_image($mime_type,$target);

    $width = getimagesize($target)[0];
    $height = getimagesize($target)[1];

    $color = imagecolorallocatealpha($img,255,255,255,80);
    imagefttext($img,64,0,$width/3,$height/2,$color,$font,$watermark);

    save_image($mime_type,$upload_dir.'watermarked/',$img,$photo['author'].$photo['title']."_watermarked");
}

function create_miniature($mime_type,$target,$upload_dir,$photo){
    $img = open_image($mime_type,$target);
    $rescaled_image = imagescale($img,200,125);
    save_image($mime_type,$upload_dir.'miniatures/',$rescaled_image,$photo['author'].$photo['title']."_miniature");
}

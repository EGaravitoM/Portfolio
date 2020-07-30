<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateUsersTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('users', function (Blueprint $table) {
            $table->increments('id');
            $table->string('name_user');
            $table->string('last_name');
            $table->string('email')->unique();
            $table->string('name')->unique();
            $table->string('password');
            $table->string('phone');
            $table->string('address');
            $table->boolean('rol');
            $table->rememberToken();
            $table->timestamps();
        });

        DB::statement("ALTER TABLE users ADD user_avatar mediumblob;");
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('users');
    }
}

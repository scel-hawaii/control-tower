import yoyo

backend = yoyo.get_backend('postgres://localhost/weatherbox')
migrations = yoyo.read_migrations('./migrations')
backend.apply_migrations(backend.to_apply(migrations))

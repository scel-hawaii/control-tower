import sys
from yoyo import get_backend, read_migrations
 
# Update this to match your database connection string
DATABASE_URL = "sqlite:///test.db"
 
def apply_specific_migration(migration_file):
    # Connect to the database
    backend = get_backend(db_uri)
 
    # Read all migrations
    migrations = read_migrations('./migrations')
 
    # Find the specific migration to apply
    selected_migration = None
    for migration in migrations:
        if migration.source.endswith(migration_file):
            selected_migration = migration
            break
 
    if not selected_migration:
        print(f"Migration file '{migration_file}' not found in ./migrations")
        return
 
    # Apply the specific migration
    if backend.is_applied(selected_migration):
        print(f"Migration '{migration_file}' has already been applied.")
    else:
        backend.apply_migrations([selected_migration])
        print(f"Migration '{migration_file}' applied successfully.")
 
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python migrate.py <migration_file>")
        sys.exit(1)
 
    migration_file = sys.argv[1]
    apply_specific_migration(migration_file)
 

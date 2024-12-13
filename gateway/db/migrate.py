import sys
import os
from yoyo import get_backend, read_migrations
from yoyo.migrations import MigrationList
 
db_uri = "postgresql://gateway@127.0.0.1/weatherbox"
 
def apply_specific_migration(migration_file):
    try:
        # Get absolute path of migrations directory
        migrations_dir = os.path.abspath('./migrations')
        print(f"Looking for migrations in: {migrations_dir}")
 
        if not os.path.exists(migrations_dir):
            print(f"Error: Migrations directory not found at {migrations_dir}")
            return
 
        # Connect to the database
        backend = get_backend(db_uri)
 
        # Check if the specific migration file exists
        migration_file_path = os.path.join(migrations_dir, migration_file)
        if not os.path.exists(migration_file_path):
            print(f"Error: Migration file not found at {migration_file_path}")
            return
 
        # Read all migrations
        all_migrations = read_migrations(migrations_dir)
 
        print("\nAttempting to apply migration...")
        # Find the specific migration
        selected_migration = None
        for migration in all_migrations:
            if os.path.basename(str(migration.id)) == os.path.splitext(migration_file)[0]:
                selected_migration = migration
                break
 
        if selected_migration:
            if backend.is_applied(selected_migration):
                print(f"Migration '{migration_file}' has already been applied.")
            else:
                # Create a proper MigrationList
                migration_list = MigrationList([selected_migration])
                backend.apply_migrations(migration_list)
                print(f"Migration '{migration_file}' applied successfully.")
        else:
            print(f"Error: Could not find matching migration for {migration_file}")
 
    except Exception as e:
        print(f"Error occurred: {str(e)}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
 
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python migrate.py <migration_file>")
        print("Example: python migrate.py create_test_table.py")
        sys.exit(1)
 
    migration_file = sys.argv[1]
    apply_specific_migration(migration_file)

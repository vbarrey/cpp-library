"use client";

import { Book } from "@/lib/api";
import { motion } from "motion/react";
import { GenresList } from "./genres-list";

type Props = {
    book: Book,
    expanded: boolean,
}

export function BookContent({ book, expanded }: Props) {
    return (
        <div className="min-w-0 flex-1 p-4">
            <h2 className="font-bold truncate">
                {book.title}
            </h2>

            <p className="text-sm text-muted-foreground">
                {book.author}
            </p>

            <GenresList genres={book.genres} />

            {expanded && (

                <motion.div
                    initial={{
                        opacity: 0,
                        y: 10,
                    }}

                    animate={{
                        opacity: 1,
                        y: 0,
                    }}

                    transition={{
                        delay: 0.2,
                    }}
                >

                    <p className="mt-4 text-sm leading-relaxed">
                        {book.description}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {book.page_count} pages
                    </p>
                </motion.div>
            )}

        </div>
    );
}